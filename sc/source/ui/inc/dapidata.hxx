/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_SC_SOURCE_UI_INC_DAPIDATA_HXX
#define INCLUDED_SC_SOURCE_UI_INC_DAPIDATA_HXX

#include <vcl/weld.hxx>

struct ScImportSourceDesc;

class ScDataPilotDatabaseDlg : public weld::GenericDialogController
{
private:
    std::unique_ptr<weld::ComboBoxText> m_xLbDatabase;
    std::unique_ptr<weld::ComboBoxText> m_xCbObject;
    std::unique_ptr<weld::ComboBoxText> m_xLbType;

    void    FillObjects();

    DECL_LINK(SelectHdl, weld::ComboBoxText&, void);

public:
    ScDataPilotDatabaseDlg(weld::Window* pParent);
    virtual ~ScDataPilotDatabaseDlg() override;

    void    GetValues( ScImportSourceDesc& rDesc );
};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
