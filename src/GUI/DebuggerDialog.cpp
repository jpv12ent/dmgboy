/*
 This file is part of DMGBoy.

 DMGBoy is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 DMGBoy is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with DMGBoy.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "IDControls.h"
#include "DebuggerDialog.h"
#include "../Debugger.h"

using namespace std;

BEGIN_EVENT_TABLE(DebuggerDialog, wxDialog)
EVT_BUTTON(ID_DEBUGRESET, DebuggerDialog::OnReset)
EVT_BUTTON(ID_DEBUGSTEPINTO, DebuggerDialog::OnStepInto)
EVT_BUTTON(ID_DEBUGONEFRAME, DebuggerDialog::OnOneFrame)
END_EVENT_TABLE()

DebuggerDialog::DebuggerDialog(wxWindow *parent, Debugger *debugger)
{
    this->Create(parent, ID_DEBUGGERDIALOG, wxT("Debugger"), wxDefaultPosition,
           wxDefaultSize, wxDEFAULT_DIALOG_STYLE);
    
    m_debugger = debugger;
    
    wxButton *resetButton = new wxButton(this, ID_DEBUGRESET, wxT("Reset"));
    wxButton *stepIntoButton = new wxButton(this, ID_DEBUGSTEPINTO, wxT("Step Into"));
    wxButton *oneFrameButton = new wxButton(this, ID_DEBUGONEFRAME, wxT("One frame"));
    resetButton->SetToolTip("Reset (Ctrl+R)");
    stepIntoButton->SetToolTip("Step Into (F7)");
    oneFrameButton->SetToolTip("One frame (Ctrl+O)");
    
    wxAcceleratorEntry entries[3];
    entries[0].Set(wxACCEL_CTRL, (int) 'R', ID_DEBUGRESET);
    entries[1].Set(wxACCEL_NORMAL, WXK_F7, ID_DEBUGSTEPINTO);
    entries[2].Set(wxACCEL_CTRL, (int) 'O', ID_DEBUGONEFRAME);
    wxAcceleratorTable accel(3, entries);
    SetAcceleratorTable(accel);
    
    wxStaticText *regsText = new wxStaticText(this, -1, wxT("Registers:"));
    
    wxFont* tmpFont = new wxFont(12, wxTELETYPE, wxNORMAL, wxNORMAL);
    
    m_regsCtrl = new wxTextCtrl(this, -1, wxEmptyString, wxDefaultPosition, wxSize(80, 90), wxTE_MULTILINE | wxTE_READONLY);
    m_regsCtrl->SetFont(*tmpFont);
    m_regsCtrl->SetValue(m_debugger->GetRegs());
    
    wxStaticText *memText = new wxStaticText(this, -1, wxT("Memory:"));
    m_memCtrl = new wxTextCtrl(this, -1, wxEmptyString, wxDefaultPosition, wxSize(420, 90), wxTE_MULTILINE | wxTE_READONLY);
    m_memCtrl->SetFont(*tmpFont);
    m_memCtrl->SetValue(m_debugger->GetMem(0x0000, 0x005F));
    
    wxSizer *buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonsSizer->Add(resetButton);
    buttonsSizer->AddSpacer(5);
    buttonsSizer->Add(stepIntoButton, 0, wxLEFT, 2);
    buttonsSizer->Add(oneFrameButton, 0, wxLEFT, 2);
    
    wxSizer *regsSizer = new wxBoxSizer(wxVERTICAL);
    regsSizer->Add(regsText, 0, wxBOTTOM, 5);
    regsSizer->Add(m_regsCtrl);
    
    wxSizer *memSizer = new wxBoxSizer(wxVERTICAL);
    memSizer->Add(memText, 0, wxBOTTOM, 5);
    memSizer->Add(m_memCtrl);
    
    wxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(buttonsSizer, 0, wxALL, 5);
    mainSizer->Add(regsSizer, 0, wxALL, 5);
    mainSizer->Add(memSizer, 0, wxALL, 5);
    
    SetSizerAndFit(mainSizer);
}

DebuggerDialog::~DebuggerDialog()
{
	
}

void DebuggerDialog::UpdateUI() {
    m_regsCtrl->SetValue(m_debugger->GetRegs());
    m_memCtrl->SetValue(m_debugger->GetMem(0x0000, 0x005F));
}

void DebuggerDialog::OnReset(wxCommandEvent &event) {
    m_debugger->Reset();
    UpdateUI();
}

void DebuggerDialog::OnStepInto(wxCommandEvent &event) {
    m_debugger->StepInto();
    UpdateUI();
}

void DebuggerDialog::OnOneFrame(wxCommandEvent &event) {
    m_debugger->ExecuteOneFrame();
    UpdateUI();
}
