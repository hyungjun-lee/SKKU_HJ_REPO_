{
//========= Macro generated from object: TPave/Legend of markers/lines/boxes to represent obj's
//========= by ROOT version6.26/06
   
   TLegend *leg = new TLegend(0.719298,0.744348,0.943609,0.918261,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextAlign(22);
   leg->SetTextFont(62);
   leg->SetTextSize(0.0313043);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000000");
   leg->SetLineColor(ci);
   leg->SetLineStyle(1);
   leg->SetLineWidth(0);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hist_0","Layer amount 4","l");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_1","Layer amount 6","l");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_2","Layer amount 8","l");
   entry->SetLineColor(3);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_3","Layer amount 10","l");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
}
