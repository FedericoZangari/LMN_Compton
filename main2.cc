/*
Questo programma esegue un fit gaussiano di un istogramma. Il programma prende in ingresso il file di dati dell'istogramma e
i canali di inizio e di fine della regione in cui si vuole eseguire il fit.
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
    cout << "Uso del programma : " << argv[0] << " <filename> <bin_min> <bin_max>" << endl;
    return -1 ;
  }  

  TApplication app("app",0,0);
  
  // leggo dati da file

  TH1F *h = ReadFillAll(argv[1]);
  h->Sumw2();
  TH1F * h2 = (TH1F*)(h->Clone("h2"));
  h->Rebin(15);
  TCanvas *c=new TCanvas();
  h->Draw();
  TF1 *f = new TF1("f", "gaus", atoi(argv[2]),atoi(argv[3]));
  h->Fit(f,"RW");
  f->Draw("same");
  Double_t mean = f->GetParameter(1);
  Double_t sigma = f->GetParameter(2);
  cout << "Valor medio: \t\t" << mean << endl;
  cout << "Deviazione standard: \t" << sigma << endl;
  cout << "Integrale entro 3 sigma: \t" << h2->Integral(mean-3*sigma, mean+3*sigma) << endl;
  cout << "Integrale totale: \t\t" << h2->Integral() << endl;
  app.Run();
}




/*

  
  
  
  TH1F *h = ReadFillAll(argv[1], argv[2], argv[3]);
  h->Sumw2();  
  cout << h->GetBinContent(2362) << endl;
	//h->StatOverflows( kTRUE );
	h->Rebin(15);
  cout << h->GetBinContent(2362) << endl;
	h->SetFillColor(kCyan-7);
  
  // disegno
  cout << h->GetBinContent(2362) << endl;
  TCanvas mycanvas ("Histo","Histo");
  //h->Draw();
  cout << h->GetBinContent(2362) << endl;
  h->GetXaxis()->SetTitle("measurement");
  TF1 *f = new TF1("f", "gaus", atoi(argv[2]),atoi(argv[3]));
  //h->GetXaxis()->SetRange(atoi(argv[2]),atoi(argv[3]));
  f->SetParLimits(1,atoi(argv[2]),atoi(argv[3]));
  f->SetParameter(2,atoi(argv[3])-atoi(argv[2]));
  cout << h->GetBinContent(2362) << endl;
  
  h->Fit(f,"RW");   
  h->Draw("");
  Double_t mean = f->GetParameter(1);
  Double_t sigma = f->GetParameter(2);
  cout << mean-sigma << "\t" << mean+sigma << endl;
  cout << h->Integral(mean-sigma, mean+sigma) << endl;
  cout << h->GetBinContent(2362) << endl;
  //cout << h->Integral();
  app.Run();
  */