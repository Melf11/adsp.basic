#pragma once
//
//  GUIDialogStereoToMS.h
//  adsp.basic
//
//  Created by Melf Stöcken on 12/10/16.
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
    
private:
    bool OnClick(int controlId);
    bool OnInit();
    
    
    static bool OnClickCB(GUIHANDLE cbhdl, int controlId);
    static bool OnInitCB(GUIHANDLE cbhdl);
    CStdString GetOnOffLabel(int onOff);
    
    const unsigned int        m_StreamId;
    int                       m_GainTestSound;
    CAddonGUIWindow          *m_window;
    CAddonGUISpinControl     *m_spinSpeakerGainTest;
    CAddonGUIRadioButton     *m_radioSpeakerContinuesTest;
};
