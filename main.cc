/*
Questo programma disegna lo spettro dei dati letti in ingresso
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

  if ( argc < 2 ) {
    cout << "Uso del programma : " << argv[0] << " <filename> " << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file

  TH1F *h = ReadFillAll(argv[1]);
  h->Sumw2();
  h->Rebin(15);

	//h->StatOverflows( kTRUE );
	

  // disegno

  TCanvas mycanvas ("Histo","Histo");
  h->Draw();
  h->GetXaxis()->SetTitle("channel");
  h->GetYaxis()->SetTitle("counts");
  string title( argv[1]);
  /*string theta = title.substr(5,3);       //per plottare gli spettri di scattering
  title = "theta" + theta +".png";
  string title2 = "Spettro #theta = " + theta + "#circ";
  h->SetTitle(title2.c_str());*/
  title = title +".png";
  mycanvas.SaveAs(title.c_str());
  app.Run();
  
}
