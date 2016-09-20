#pragma once
//
//  GUIDialogStereoToMS.h
//  adsp.basic
//
//  Created by Melf Stöcken on 09.09.16.
//
//

#include <string>

#include "AudioDSPSettings.h"

class CGUIDialogStereoToMS : private CDSPSettings
{
public:
    CGUIDialogStereoToMS(unsigned int streamId);
    virtual ~CGUIDialogStereoToMS();
    
    bool Show();
    void Close();
    void DoModal();
    
    //void ContinuesTestSwitchInfoCB(AE_DSP_CHANNEL channel);
    
private:
    bool OnClick(int controlId);
    //bool OnFocus(int controlId);
    bool OnInit();
  //  bool OnAction(int actionId);
    
    static bool OnClickCB(GUIHANDLE cbhdl, int controlId);
   // static bool OnFocusCB(GUIHANDLE cbhdl, int controlId);
    static bool OnInitCB(GUIHANDLE cbhdl);
   // static bool OnActionCB(GUIHANDLE cbhdl, int actionId);
    
    CStdString GetOnOffLabel(int onOff);
    
    const unsigned int        m_StreamId;
    int                       m_GainTestSound;
    CAddonGUIWindow          *m_window;
    CAddonGUISpinControl     *m_spinSpeakerGainTest;
    CAddonGUIRadioButton     *m_radioSpeakerContinuesTest;
};
