void energia(){
    string title = "energia.dat";
    ifstream f(title.c_str());
    TGraphErrors *g = new TGraphErrors();
    TGraph *e = new TGraph(); 
    TCanvas *c = new TCanvas("c","c");
    Double_t x, err_x, err_y, y;

    for(int i = 0; i < 6; i++){
        f >> x >> err_x >> y >> err_y;
        g->SetPoint(i, x, y);
        g->SetPointError(i, err_x, err_y);
        e->SetPoint(i, x, 511/(2-cos(x*M_PI/180.)));
    }
    g->GetXaxis()->SetTitle("#theta [#circ]");
    g->GetYaxis()->SetTitle("Energia [keV]");
    //g->GetXaxis()->SetRangeUser(1800,10000);
    g->SetTitle("Energia fotoni Compton");
    g->SetMarkerStyle(43);
	g->SetMarkerSize(1.5);
    g->SetMarkerColor(kSpring+4);
    e->SetMarkerStyle(20);
	e->SetMarkerSize(1);
    e->SetMarkerColor(kTeal);
    TLegend *l = new TLegend(0.6,0.7,0.89,0.9);
    l->AddEntry(g, "Dati sperimentali", "ple");
    l->AddEntry(e, "Energia teorica", "pl");
    
    
    g->Draw("AP");
    e->Draw("CP");
    l->Draw("same");
    c->SaveAs("energia.png");
}