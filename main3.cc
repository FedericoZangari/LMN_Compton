/*
Il programma legge in ingresso il file di dati del background e lo spettro in funzione dell'angolo con il suo tempo di acquisizione, restituisce in output un file in cui 
allo spettro misurato viene sottratto il background riscalato per il rapporto dei tempi di acquisizione.
*/

#include <iostream>
#include <fstream>
#include "TH1F.h"
#include "TF1.h"
#include "TApplication.h"
#include "TCanvas.h"

using namespace std;

TH1F* ReadFillAll( const char* Filename) {
    
	ifstream f(Filename);
  TH1F *h1 = new TH1F("h1", "Spettro", 7725, 0, 7725);
  int i = 0;
	if(!f){
  		cerr <<"Error: cannot open file " <<endl;
		exit(0);
	}
  else{
      double var;
			for (;;){
					
          f >> var;
          h1->SetBinContent(i,var);		
									
					if(f.eof()){
						cout << "End of file reached "<< endl;
						break;
					}
          i++;		
			}
		}	f.close();

	return h1;
}


int main( int argc , char** argv ) {

  if ( argc < 4 ) {
    cout << "Uso del programma : " << argv[0] << " <background_file> <spettro_file> <tempo di acquisizione>" << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file
  double scale = atof(argv[3])/314353.;  //riscalo per il rapporto dei tempi di acquisizione
  TH1F *bkg = ReadFillAll(argv[1]);
  TH1F *sig = ReadFillAll(argv[2]);
  string title( argv[2]);
  string theta = title.substr(5,2);
  //string theta = title.substr(5,3);   // per fare il plot a theta = 150

 
	bkg->StatOverflows( kTRUE );
  sig->StatOverflows( kTRUE );
  bkg->Sumw2();
  sig->Sumw2();
	
	bkg->SetLineColor(kCyan);
  
  TCanvas can1 ("c","c");
  bkg->Draw();
  bkg->SetTitle("Spettro di background");
  bkg->GetXaxis()->SetTitle("Numero del canale MCA");
  bkg->GetYaxis()->SetTitle("Conteggi per canale");
  can1.SaveAs("background.png");

  TCanvas mycanvas ("Histo","Histo");
  mycanvas.cd();
  TH1F * bkg2 = (TH1F*)(bkg->Clone("bkg2"));
  bkg2->Scale(scale);
  //bkg->Draw();
  sig->Add(bkg2,-1);

  for(int i =0; i< 7725; i++){
        if (sig->GetBinContent(i) < 0.) sig->SetBinContent(i, 0.0);
  }
  string title3 = "theta" + theta +"_parsed.dat";
  ofstream out(title3.c_str());
  for(int i =0; i< 7725; i++){
        out << sig->GetBinContent(i) << endl;
  }

  sig->SetLineColor(kRed);
  string title2 = "Spettro senza background #theta = " + theta + "#circ"; 
  sig->SetTitle(title2.c_str());
  sig->GetXaxis()->SetTitle("Numero del canale MCA");
  sig->GetYaxis()->SetTitle("Conteggi per canale");
  sig->Rebin(15);
  sig->Draw();
  string title4 = "theta" + theta +"_parsed.png";
  mycanvas.SaveAs(title4.c_str());
    
  
  app.Run();
  
}
