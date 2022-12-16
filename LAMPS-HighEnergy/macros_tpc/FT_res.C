void FT_res()
{
    TFile *MCfilename = new TFile("out_g4event_LH.mc.root", "READ");
    TTree *MCfiletree = (TTree *)MCfilename->Get("event");
    
    TFile *KBfilename = new TFile("out_g4event_LH.conv.eb7a905.root", "READ");
    TTree *KBfiletree = (TTree *)KBfilename->Get("event");
}