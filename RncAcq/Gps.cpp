
#include <boost/thread/thread.hpp> 
#include <boost/tokenizer.hpp>
#include "Gps.h"
#include "LogMgr.h"

//----------------------------------------------------------------------------------
Gps::Gps(Model *model)
{
	mmodel = model;
	mgpsData.velocidade = 0;
	mgpsData.direcao = 0;
	mgpsData.latitude.valor = 0;
	mgpsData.longitude.valor = 0;
	mgpsData.estado = GPS_TIMEOUT;
	mgpsData.ParserGGA = false;
	mgpsData.ParserRMC = false;
	mgpsData.receiverWarning = 0;
	mEstado = 0;
	mterminaThread = false;
	mtolerancia = 0;

	message_queue::remove(NOME_CTRL_COORDENADAS_QUEUE);
	mq.reset(new message_queue(create_only, NOME_CTRL_COORDENADAS_QUEUE, 8, sizeof(GPSDATA)));
}

//---------------------------------------------------------------------------------
Gps::~Gps()
{
}

//---------------------------------------------------------------------------------
bool Gps::Passo1(char *Token)
{
	return(strcmp(Token, "$GPRMC") == 0);
}

//---------------------------------------------------------------------------------
bool Gps::Passo2(char *Token)
{
	//hora UTC (hhmmss.ss)
	mgpsData.hora = Token;
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::Passo3(char *Token)
{
	//'A' for fix valid (V for invalid or no fix)
	mgpsData.receiverWarning = Token[0];
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::Passo4(char *Token)
{
	// Converte de ddmm.mmmm para décimos de segundo de grau
	mgpsData.latitude.valor =	(long)
								(
									(double) (10*(Token[0]-0x30)+(Token[1]-0x30))*36000 +    
									(double)(10*(Token[2]-0x30)+(Token[3]-0x30))*600  +
					 				(double)((1000*(Token[5]-0x30)+100*(Token[6]-0x30)+10*(Token[7]-0x30)+(Token[8]-0x30))*6)/100
								);

	return strlen(Token) > 0;
}

//---------------------------------------------------------------------------------
bool Gps::Passo5(char *Token)
{
	//N for North, S for South
	char hLat = Token[0];
	mgpsData.latitude.hemisferio = 'S';

	// Converte (SUL valor negativo de 0 a -3240000 graus) 
	if (hLat == 'S')
	{
		mgpsData.latitude.valor *= -1;  
	}

	return (hLat == 'N' || hLat == 'S');
}

//---------------------------------------------------------------------------------
bool Gps::Passo6(char *Token)
{
	// Converte de dddmm.mmmm para décimos de segundo de grau 
	mgpsData.longitude.valor =	(long)
								(
									(double)(100*(Token[0]-0x30)+10*(Token[1]-0x30)+(Token[2]-0x30))*36000 +    
									(double)(10*(Token[3]-0x30)+(Token[4]-0x30))*600 +
		 							(double)((1000*(Token[6]-0x30)+100*(Token[7]-0x30)+10*(Token[8]-0x30)+(Token[9]-0x30))*6)/100
								);

	//longitude (dddmm.mmmm format) 
	return strlen(Token) > 0;
}

//---------------------------------------------------------------------------------
bool Gps::Passo7(char *Token)
{
	//E for East, W for West
	char hLon = Token[0];

	mgpsData.longitude.hemisferio = hLon;
	// Converte (OESTE valor negativo de 0 a -12960000).
	if (hLon == 'W')
	{
		mgpsData.longitude.valor *= -1;
	}

	return (hLon == 'E' || hLon == 'W');
}

//---------------------------------------------------------------------------------
bool Gps::Passo8(char *Token)
{
	// speed over ground em knots (0000.0 to 1851.8) 
	// 1 knot = 1.852 km/h 
	mgpsData.velocidade = (float)(1.852F * atof(Token));
	return strlen(Token) > 0;
}

//---------------------------------------------------------------------------------
bool Gps::Passo9(char *Token)
{
	//course over ground (000.0 to 359.9)
	mgpsData.direcao = (unsigned int) (atof(Token) + 0.5F);
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::Passo10(char *Token)
{
	//data (ddmmyy format)
	mgpsData.data = Token;
	return mgpsData.data.size() > 0;
}

//----------------------------------------------------------------------------------
void Gps::CalculaBcc(char *sBcc)
{
	unsigned int i;
	int Bcc;
	char carac;

	//xor de todos os bytes dentro da sentenca entre $ e *
	//valor convertido para dois caracteres ASC

	for(i = 1, Bcc = 0; i < mSentenca.size() && (carac = mSentenca[i]) != '*'; i++)
	{
		Bcc ^= carac;
	}

	stringstream bccsafe;
	string bccstr;

	bccsafe << uppercase << hex << setw(2) << setfill('0') << Bcc; 
	bccsafe >> bccstr; 
	
	sBcc[0] = bccstr[0];
	sBcc[1] = bccstr[1];
}

//----------------------------------------------------------------------------------
bool Gps::VerificaBcc()
{
	char Bcc[3];
	int pont;
	bool retval = false;

	CalculaBcc(Bcc);
	pont = mSentenca.find('*');

	if(pont != string::npos)
	{
		//evitar que pont acesse memoria maior que mSentenca (caso '*' esteja no último endereço de mSentenca)
		if(mSentenca.size() > (unsigned int)(pont + 2) ) 
		{
			char bcc1 = mSentenca[pont + 1];
			char bcc2 = mSentenca[pont + 2];

			if(bcc1 == Bcc[0] && bcc2 == Bcc[1])
			{
				retval = true;
			}
			else
			{

				CalculaBcc(Bcc);
				retval = false;
			}
		}
	}

	return retval;
}

//----------------------------------------------------------------------------------
bool Gps::ParserRMC()
{
	bool retval = false;
	
	mgpsData.ParserRMC = false;

	bool (Gps::*pFunc[])(char *) = 
	{
		&Gps::Passo1,
		&Gps::Passo2,
		&Gps::Passo3,
		&Gps::Passo4,
		&Gps::Passo5,
		&Gps::Passo6,
		&Gps::Passo7,
		&Gps::Passo8,
		&Gps::Passo9,
		&Gps::Passo10
	};

	if(VerificaBcc())
	{
		int i = 0;

		string tokstr;

		//variavel para tokenizar a sentenca
		boost::char_separator<char> sep(",");
		boost::tokenizer< boost::char_separator<char> >tok(mSentenca, sep);

		for(boost::tokenizer< boost::char_separator <char> >::iterator beg = tok.begin(); i < 10 && beg != tok.end(); beg++)
		{
			stringstream(*beg) >> tokstr;

			//pula token $ e , 
			//tokenizer mantem os separadores como token
			if(tokstr != "$" && tokstr != ",")
			{
				bool ret = (this->*pFunc[i++])((char *)tokstr.c_str());
				if(!ret)
				{
					break;
				}
			}
		}

		// Leitura correta do pacote RMC
		if ( i == 10 ) 
		{
			mgpsData.ParserRMC = true;

			if(mgpsData.receiverWarning == 'A')
			{
				retval = true;
			}
			else
			{
				retval = false;
			}
		}
	}

	return retval;
}

//---------------------------------------------------------------------------------
bool Gps::PassoGGA( char *Token )
{
	return( strcmp( Token, "$GPGGA" ) == 0);
}

//---------------------------------------------------------------------------------
bool Gps::PassoVazio( char *Token )
{
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::PassoNroSat( char *Token )
{
	mgpsData.nroSatelites = ( unsigned int ) atoi ( Token );
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::PassoHDOP( char *Token )
{
	mgpsData.HDOP = ( float )atof ( Token );
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::PassoAltitude( char *Token )
{
	mgpsData.altitude = ( float )atof ( Token );
	return true;
}

//---------------------------------------------------------------------------------
bool Gps::ParserGGA()
{
	bool retval = false;

	mgpsData.ParserGGA = false;

	// formato do pacote
	//$GPGGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh
	
	bool (Gps::*pFunc[])(char *) = 
	{
		&Gps::PassoGGA,
		&Gps::PassoVazio,	// horario
		&Gps::PassoVazio,	// latitude
		&Gps::PassoVazio,	// hemisfério
		&Gps::PassoVazio,	// longitude
		&Gps::PassoVazio,	// hemisfério
		&Gps::PassoVazio,	// Indicador de qualidade
		&Gps::PassoNroSat,	// Número de satélites em uso
		&Gps::PassoHDOP,	// HDOP
		&Gps::PassoAltitude		//altitude da antena nivel do mar
	};

	
	if(VerificaBcc())
	{
		int i = 0;

		string tokstr;

		//variavel para tokenizar a sentenca
		boost::char_separator<char> sep(",");
		boost::tokenizer< boost::char_separator<char> >tok(mSentenca, sep);

		for(boost::tokenizer< boost::char_separator <char> >::iterator beg = tok.begin(); i < 10 && beg != tok.end(); beg++)
		{
			stringstream(*beg) >> tokstr;

			//pula token $ e , 
			//tokenizer mantem os separadores como token
			if(tokstr != "$" && tokstr != ",")
			{
				bool ret = (this->*pFunc[i++])((char *)tokstr.c_str());
				if(!ret)
				{
					break;
				}
			}
		}

		if(i == 10)
		{
			mgpsData.ParserGGA = true;
			retval = true;

			//vdop e hdop estão presentes em GSA que não é tratada nesta versão
			mgpsData.VDOP = 0;
			mgpsData.PDOP = 0;
		}
	}

	return retval;
}

//----------------------------------------------------------------------------------
bool Gps::LeSentenca()
{
	bool retval = false;

	mSentenca.clear();
	
	try
	{
		mSentenca = mSerial.readStringUntil("\r\n");
		retval = true;
	}
	catch(...)
	{
		retval = false;
	}

	return retval;
}

//----------------------------------------------------------------------------------
void Gps::EnviaSentenca(char *Sentenca, int Tam)
{
	mSerial.write(Sentenca, Tam);
}

//----------------------------------------------------------------------------------
int Gps::MontaSentencaConfTrimble(char *sent)
{
	int tam = 44;

	float elevationMask = (float) 0.0873;
	float AMUmask = 6.0;
	float PDOPMask = 6.0;

	memset(sent, 0xFF, 44);
	sent[0] = 0x10;
	sent[1] = (char) 0xBB; // comando
	sent[2] = 0x00; // subcode
	sent[3] = 0x00; // operating dimension
	sent[4] = 0x03; // dgps mode (0x03 = auto)
	sent[5] = 0x01; // dynamic code (0x01 = land)
	sent[6] = 0x00; // solution mode
	// Elevation Mask
	sent[7] =  *(((char *)&elevationMask)+3);
	sent[8] =  *(((char *)&elevationMask)+2);
	sent[9] =  *(((char *)&elevationMask)+1);
	sent[10] = *(((char *)&elevationMask));
	// AMU Mask
	sent[11] = *(((char *)&AMUmask)+3);
	sent[12] = *(((char *)&AMUmask)+2);
	sent[13] = *(((char *)&AMUmask)+1);
	sent[14] = *(((char *)&AMUmask));
	// PDOP Mask
	sent[15] = *(((char *)&PDOPMask)+3);
	sent[16] = *(((char *)&PDOPMask)+2);
	sent[17] = *(((char *)&PDOPMask)+1);
	sent[18] = *(((char *)&PDOPMask));
	// PDOP Swith valor default
	sent[19] = 0x40; 
	sent[20] = (char) 0xC0; 
	sent[21] = 0x00;
	sent[22] = 0x00;
	sent[23] = 0x1E; //DGPS Age Limits
	sent[24] = 0x01; //Foliage mode (0x01 sometimes)
	sent[25] = 0x00; //Low power modem (0x00 disable)
	sent[26] = 0x00; //Clock Hold Mode (0x00 disable)
	sent[27] = 0x00; //Measurement Rate (0x00 1Hz)
	sent[28] = 0x00; //Position Fix Rate (0x00 1Hz)
	// o restante dos bytes é reservado e preenchido com 0xFF
	sent[42] = 0x10;
	sent[43] = 0x03;
	return tam;
}
//----------------------------------------------------------------------------------
void Gps::ProgramaGpsSerial()
{
	//sentencas Garmin
	char GarminDesligaSentencas[] = "$PGRMO,,2\r\n";
	char GarminLigaSentencas[] = "$PGRMO,,3\r\n";
	char GarminLigaGPRMC[] = "$PGRMO,GPRMC,1\r\n";
	char GarminLigaGPGSV[] = "$PGRMO,GPGSV,1\r\n";
	char GarminLigaGPGGA[] = "$PGRMO,GPGGA,1\r\n";

	//enviando sentencas Garmin
	EnviaSentenca(GarminDesligaSentencas, strlen(GarminDesligaSentencas));
	boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

	EnviaSentenca(GarminLigaGPRMC, strlen(GarminLigaGPRMC));
	boost::this_thread::sleep(boost::posix_time::milliseconds(200));
	// Habilita sentença GGA para utilização em filtro (nro satelite + HDOP)
	EnviaSentenca(GarminLigaGPGGA, strlen(GarminLigaGPGGA));
	boost::this_thread::sleep(boost::posix_time::milliseconds(200));
}

//---------------------------------------------------------------------------------
bool Gps::VerificaSentenca()
{
	bool retval;

	if(mSentenca.find("$GPRMC") != string::npos)
	{
		//inicializa leitura de RMC
		mgpsData.ParserRMC = false;

		if ( ParserRMC() )
		{
			mgpsData.ParserRMC = true;	
		}
	}
	else if(mSentenca.find("$GPGGA") != string::npos)
	{
		//inicializa leitura de GGA
		mgpsData.ParserGGA = false;

		if ( ParserGGA() )
		{
			mgpsData.ParserGGA = true;
		}
	}
	else if( mSentenca.find("$GPGSA") != string::npos)
	{
		// Executa o Parser do pacote GSA.
	}
	else if( mSentenca.find("$GPGSV") != string::npos)
	{
		//IGNORA SENTENÇA
	}
	else if( mSentenca.find("$PGRMO") != string::npos)
	{
		//IGNORA SENTENÇA
		//GPRMO É SENTENÇA DE CONFIRMAÇÃO DE CONFIGURAÇÃO
	}

	//retorna estrutura apenas se PRMC & GGA foram lidas
	if(mgpsData.ParserRMC && mgpsData.ParserGGA)
	{
		retval = true;
	}
	else
	{
		retval = false;
	}

	return retval;
}

//---------------------------------------------------------------------------------
void Gps::Inicia(string com)
{
	mterminaThread = false;

	if(!mSerial.isOpen())
	{
		mSerial.open(com.c_str(), 4800);
		//um segundo de timeout
		mSerial.setTimeout(boost::posix_time::seconds(1));

		mThread = boost::thread(Thread, this);  
	}
}

//---------------------------------------------------------------------------------
void Gps::Termina()
{
	mterminaThread = true;
	//aguarda thread terminar
	mThread.join();
}

//---------------------------------------------------------------------------------
void Gps::Thread(Gps *gps)
{
	gps->Run();
}

//---------------------------------------------------------------------------------
void Gps::EnviaSentenca(char *sentenca)
{
	//envia via message queue para CtrlCoordenadas
}

//---------------------------------------------------------------------------------
bool Gps::VerificaSerialAtiva()
{
	return mSerial.isOpen();
}

//---------------------------------------------------------------------------------
void Gps::EnviaParaCtrlCoordenadas()
{
//	message_queue::remove(NOME_CTRL_COORDENADAS_QUEUE);
	try
	{
		mq->send((const char *)&mgpsData, sizeof(GPSDATA), 0);
	}
	catch(...)
	{
//		message_queue::remove(NOME_CTRL_COORDENADAS_QUEUE);
	}

	//envia dados para CtrlCoordenadas via message_queue
//	mgpsQueue.Send((const char *)(&mgpsData));
}

//---------------------------------------------------------------------------------
void Gps::GravaLog()
{
	LogMgr::GetInstance()->Escreve("SENTENCA", mSentenca);
}

//---------------------------------------------------------------------------------
void Gps::ProcessaSentenca()
{

	if ( VerificaSentenca() )
	{
		//recebeu as sentenças GPRMC & GGA
		//verifica se sentenca GPRMC está válida
		if( mgpsData.receiverWarning == 'A' )
		{
			//envia dados do GPS para controlador de coordenadas
			EnviaParaCtrlCoordenadas();

			//indica que a sentenca GPRMC é válida e recebeu tmabém a GGA (icone GPS verde)
			mmodel->GuiSentencaOk();
			//atualiza 
			mmodel->GuiSetHdop(mgpsData.HDOP);
		}
		else
		{
			//indica sentenca invalida-> ativa icone amarelo
			mmodel->GuiErroGpsSentencaInvalida();
		}

		mtolerancia = 0;
	}
	else
	{
		//não recebeu as sentencas GPRMC & GGA
		if(mtolerancia > 4)
		{
			//com tolerancia de 4 leituras avisa GUI que
			//não recebeu as sentencas esperadas (icone amarelo)
			mmodel->GuiErroGpsSentencaInvalida();
		}
		else
		{
			mtolerancia++;
		}
	}
}

//---------------------------------------------------------------------------------
void Gps::Run()
{
	while(!mterminaThread)
	{

		if(VerificaSerialAtiva())
		{
			switch (mEstado) 
			{
			case 0:
				//programa sentencas do GPS
				ProgramaGpsSerial();
				mEstado = 1;
			break;

			case 1:
				// Leitura de sentença, pode ser RMC, GGA ou RMO(programação)
				if( LeSentenca() == true )
				{
					//grava sentenca no log-> se estiver em modo gravação
					GravaLog();

					//verifica se recebeu as sentencas esperadas e aciona os ícones
					ProcessaSentenca();
				}
				else
				{
					//avisar GUI que não está recebendo sentenças (icone vermelho)
					mmodel->GuiErroGpsFalhaSentenca();
					mmodel->GuiSetHdop(HDOP_FIMESCALA);
					boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
				}
			break;
			}

			//delay loop principal da thread
			boost::this_thread::sleep(boost::posix_time::milliseconds(100));
		}
		else
		{
			mterminaThread = true;
		}
	}

	//envia mensagem para GUI e termina thread
	mmodel->GuiErroGps();
	mmodel->GuiSetHdop(HDOP_FIMESCALA);
	mSerial.close();
}

