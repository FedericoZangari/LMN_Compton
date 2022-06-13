void calibration(){
    string title = "calibrazione.dat";
    ifstream f(title.c_str());
    TGraphErrors *g = new TGraphErrors(); 
    TCanvas *c = new TCanvas("c","c");
    Double_t x, err_x, y;

    for(int i = 0; i < 4; i++){
        f >> x >> err_x >> y;
        g->SetPoint(i, x, y);
        g->SetPointError(i, err_x, 0.);
    }
    g->GetXaxis()->SetTitle("Numero del canale MCA");
    g->GetYaxis()->SetTitle("Energia [keV]");
    //g->GetXaxis()->SetRangeUser(1800,10000);
    g->SetTitle("Retta di calibrazione");
    g->Fit("pol1");
    g->SetMarkerStyle(43);
	g->SetMarkerSize(1.5);
    g->SetMarkerColor(kSpring+4);
    g->Draw("AP");
    c->SaveAs("retta_calibrazione.png");


}