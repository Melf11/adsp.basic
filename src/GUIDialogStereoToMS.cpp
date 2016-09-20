//
//  GUIDialogStereoToMS.cpp
//  adsp.basic
//
//  Created by Melf Stöcken on 09.09.16.
//
//

#include "libXBMC_addon.h"
#include "libKODI_adsp.h"
#include "libKODI_guilib.h"

#include "util/XMLUtils.h"
#include "p8-platform/util/util.h"
#include "p8-platform/util/StdString.h"

#include "GUIDialogStereoToMS.h"
#include "AudioDSPSoundTest.h"

#define BUTTON_OK                                 1
#define BUTTON_CANCEL                             2

#define SPIN_CONTROL_STEREO_TO_MS                10
#define MS_ON                                    11
#define MS_OFF                                   12

#define ACTION_NAV_BACK                          92


CGUIDialogStereoToMS::CGUIDialogStereoToMS(unsigned int streamId)
: m_StreamId(streamId)
, m_window(NULL)

//, m_GainTestSound(SOUND_TEST_OFF)
//, m_spinSpeakerGainTest(NULL)
//, m_radioSpeakerContinuesTest(NULL)
{
    m_window              = GUI->Window_create("DialogStereoToMS.xml", "skin.estuary", false, true);
    m_window->m_cbhdl     = this;
    m_window->CBOnInit    = OnInitCB;
    //m_window->CBOnFocus   = OnFocusCB;
    m_window->CBOnClick   = OnClickCB;
    //m_window->CBOnAction  = OnActionCB;
}

CGUIDialogStereoToMS::~CGUIDialogStereoToMS()
{
    GUI->Window_destroy(m_window);
}
 
bool CGUIDialogStereoToMS::OnInitCB(GUIHANDLE cbhdl)
{
    CGUIDialogStereoToMS* dialog = static_cast<CGUIDialogStereoToMS*>(cbhdl);
    return dialog->OnInit();
}

bool CGUIDialogStereoToMS::OnClickCB(GUIHANDLE cbhdl, int controlId)
{
    CGUIDialogStereoToMS* dialog = static_cast<CGUIDialogStereoToMS*>(cbhdl);
    return dialog->OnClick(controlId);
}
/*
bool CGUIDialogStereoToMS::OnFocusCB(GUIHANDLE cbhdl, int controlId)
{
    CGUIDialogStereoToMS* dialog = static_cast<CGUIDialogStereoToMS*>(cbhdl);
    return dialog->OnFocus(controlId);
}

bool CGUIDialogStereoToMS::OnActionCB(GUIHANDLE cbhdl, int actionId)
{
    CGUIDialogStereoToMS* dialog = static_cast<CGUIDialogStereoToMS*>(cbhdl);
    return dialog->OnAction(actionId);
}
 */
bool CGUIDialogStereoToMS::Show()
{
    if (m_window)
        return m_window->Show();
    
    return false;
}

void CGUIDialogStereoToMS::Close()
{
    if (m_window)
        m_window->Close();
}

void CGUIDialogStereoToMS::DoModal()
{
    if (m_window)
        m_window->DoModal();
}

bool CGUIDialogStereoToMS::OnInit()
{
    LoadSettingsData(ID_MENU_STEREO_TO_MS);
    

    return true;
}

bool CGUIDialogStereoToMS::OnClick(int controlId)
{
    AE_DSP_CHANNEL channelId = TranslateGUIIdToChannelId(controlId);
    if (channelId != AE_DSP_CH_MAX)
    {
        g_DSPProcessor.SetDelay(channelId, m_Settings.m_channels[channelId].ptrSpinControl->GetValue());
       // SetInfoLabel(channelId);
    }
    else
    {
        switch (controlId)
        {
            case BUTTON_CANCEL:
            {
                m_window->Close();
              
                
                break;
            }
            case BUTTON_OK:
            {
                m_window->Close();
                /*
                
                if (m_StereoToMS) {
                    <#statements#>
                }
                */
                
                
                //GUI->Control_releaseSpin(m_spinSpeakerDistanceUnit);
                for (int i = 0; i < AE_DSP_CH_MAX; ++i)
                {
                    if (m_Settings.m_channels[i].ptrSpinControl)
                    {
                        m_Settings.m_channels[i].iDistanceCorrection = m_Settings.m_channels[i].ptrSpinControl->GetValue();
                        GUI->Control_releaseSpin(m_Settings.m_channels[i].ptrSpinControl);
                    }
                }
                SaveSettingsData();
                break;
            }
            default:
                break;
        }
    }

    return true;
}
