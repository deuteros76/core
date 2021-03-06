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
#ifndef INCLUDED_SD_SOURCE_UI_DLG_SDDLGFACT_HXX
#define INCLUDED_SD_SOURCE_UI_DLG_SDDLGFACT_HXX

#include <sdabstdlg.hxx>
#include <sfx2/basedlgs.hxx>
#include <sfx2/sfxdlg.hxx>

#define DECL_ABSTDLG_BASE(Class,DialogClass)            \
    ScopedVclPtr<DialogClass> pDlg;                     \
public:                                                 \
    explicit Class(DialogClass* p)                      \
        : pDlg(p)                                       \
    {                                                   \
    }                                                   \
    virtual std::vector<OString> getAllPageUIXMLDescriptions() const override; \
    virtual bool selectPageByUIXMLDescription(const OString& rUIXMLDescription) override; \
    virtual BitmapEx createScreenshot() const override;   \
    virtual OString GetScreenshotId() const override;   \
    virtual         ~Class() override;                           \
    virtual short   Execute() override ;

#define IMPL_ABSTDLG_BASE(Class)                    \
std::vector<OString> Class::getAllPageUIXMLDescriptions() const { return pDlg->getAllPageUIXMLDescriptions(); } \
bool Class::selectPageByUIXMLDescription(const OString& rUIXMLDescription) { return pDlg->selectPageByUIXMLDescription(rUIXMLDescription); } \
BitmapEx Class::createScreenshot() const { return pDlg->createScreenshot();} \
OString Class::GetScreenshotId() const { return pDlg->GetScreenshotId();} \
Class::~Class()                                     \
{                                                   \
}                                                   \
short Class::Execute()                              \
{                                                   \
    return pDlg->Execute();                         \
}

namespace sd {
    class MorphDlg;
    class CopyDlg;
    class BreakDlg;
    class HeaderFooterDialog;
    class MasterLayoutDialog;
    class OutlineBulletDlg;
}

class Dialog;
class SdVclAbstractDialog_Impl : public VclAbstractDialog
{
    DECL_ABSTDLG_BASE(SdVclAbstractDialog_Impl,Dialog)
};

class SdAbstractGenericDialog_Impl : public VclAbstractDialog
{
protected:
    std::unique_ptr<weld::GenericDialogController> m_xDlg;
public:
    explicit SdAbstractGenericDialog_Impl(std::unique_ptr<weld::GenericDialogController> p)
        : m_xDlg(std::move(p))
    {
    }
    virtual short Execute() override;
};

class AbstractMasterLayoutDialog_Impl : public VclAbstractDialog
{
private:
    std::unique_ptr<sd::MasterLayoutDialog> m_xDlg;
public:
    AbstractMasterLayoutDialog_Impl(std::unique_ptr<::sd::MasterLayoutDialog> pDlg);
    virtual short Execute() override;
};

class AbstractBreakDlg_Impl : public VclAbstractDialog
{
private:
    std::unique_ptr<sd::BreakDlg> m_xDlg;
public:
    AbstractBreakDlg_Impl(std::unique_ptr<::sd::BreakDlg> pDlg);
    virtual short Execute() override;
};

class AbstractCopyDlg_Impl : public AbstractCopyDlg
{
    DECL_ABSTDLG_BASE(AbstractCopyDlg_Impl,::sd::CopyDlg)
    virtual void    GetAttr( SfxItemSet& rOutAttrs ) override;
};

class SdCustomShowDlg;
class AbstractSdCustomShowDlg_Impl : public AbstractSdCustomShowDlg
{
private:
    std::unique_ptr<SdCustomShowDlg> m_xDlg;
public:
    AbstractSdCustomShowDlg_Impl(std::unique_ptr<SdCustomShowDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short       Execute() override;
    virtual bool        IsModified() const override ;
    virtual bool        IsCustomShow() const override ;
};

class SfxTabDialog;
class SdAbstractTabDialog_Impl : public SfxAbstractTabDialog
{
    DECL_ABSTDLG_BASE( SdAbstractTabDialog_Impl,SfxTabDialog )
    virtual void                SetCurPageId( const OString& rName ) override;
    virtual const SfxItemSet*   GetOutputItemSet() const override;
    virtual const sal_uInt16*       GetInputRanges( const SfxItemPool& pItem ) override;
    virtual void                SetInputSet( const SfxItemSet* pInSet ) override;
        //From class Window.
    virtual void        SetText( const OUString& rStr ) override;
};

class AbstractBulletDialog_Impl : public SfxAbstractTabDialog
{
    DECL_ABSTDLG_BASE( AbstractBulletDialog_Impl,SfxTabDialog )
    virtual void                SetCurPageId( const OString& rName ) override;
    virtual const SfxItemSet*   GetOutputItemSet() const override;
    virtual const sal_uInt16*       GetInputRanges( const SfxItemPool& pItem ) override;
    virtual void                SetInputSet( const SfxItemSet* pInSet ) override;
        //From class Window.
    virtual void        SetText( const OUString& rStr ) override;
};

class SdPresLayoutTemplateDlg;
class SdPresLayoutTemplateDlg_Impl : public SfxAbstractTabDialog
{
    DECL_ABSTDLG_BASE( SdPresLayoutTemplateDlg_Impl,SdPresLayoutTemplateDlg )
    virtual void                SetCurPageId( const OString& rName ) override;
    virtual const SfxItemSet*   GetOutputItemSet() const override;
    virtual const sal_uInt16*       GetInputRanges( const SfxItemPool& pItem ) override;
    virtual void                SetInputSet( const SfxItemSet* pInSet ) override;
        //From class Window.
    virtual void        SetText( const OUString& rStr ) override;
};

class SdModifyFieldDlg;
class AbstractSdModifyFieldDlg_Impl : public AbstractSdModifyFieldDlg
{
private:
    std::unique_ptr<SdModifyFieldDlg> m_xDlg;
public:
    AbstractSdModifyFieldDlg_Impl(std::unique_ptr<SdModifyFieldDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short Execute() override;
    virtual SvxFieldData*       GetField() override;
    virtual SfxItemSet          GetItemSet() override;
};

class SdSnapLineDlg;
class AbstractSdSnapLineDlg_Impl : public AbstractSdSnapLineDlg
{
private:
    std::unique_ptr<SdSnapLineDlg> m_xDlg;
public:
    AbstractSdSnapLineDlg_Impl(std::unique_ptr<SdSnapLineDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short Execute() override;
    virtual void GetAttr(SfxItemSet& rOutAttrs) override;
    virtual void HideRadioGroup() override;
    virtual void HideDeleteBtn() override;
    virtual void SetInputFields(bool bEnableX, bool bEnableY) override;
    //from class Window
    virtual void    SetText( const OUString& rStr ) override;
};

class SdInsertLayerDlg;
class AbstractSdInsertLayerDlg_Impl : public AbstractSdInsertLayerDlg
{
private:
    std::unique_ptr<SdInsertLayerDlg> m_xDlg;
public:
    AbstractSdInsertLayerDlg_Impl(std::unique_ptr<SdInsertLayerDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short   Execute() override;
    virtual void    GetAttr( SfxItemSet& rOutAttrs ) override ;
    //from class Window
    virtual void    SetHelpId( const OString& rHelpId ) override ;
};

class SdInsertPagesObjsDlg;
class AbstractSdInsertPagesObjsDlg_Impl : public AbstractSdInsertPagesObjsDlg
{
    DECL_ABSTDLG_BASE(AbstractSdInsertPagesObjsDlg_Impl,SdInsertPagesObjsDlg)
    virtual std::vector<OUString> GetList ( const sal_uInt16 nType ) override;
    virtual bool        IsLink() override;
    virtual bool        IsRemoveUnnessesaryMasterPages() const override;
};

class AbstractMorphDlg_Impl : public AbstractMorphDlg
{
private:
    std::unique_ptr<sd::MorphDlg> m_xDlg;
public:
    AbstractMorphDlg_Impl(std::unique_ptr<::sd::MorphDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short   Execute() override;
    virtual void            SaveSettings() const override;
    virtual sal_uInt16      GetFadeSteps() const override;
    virtual bool            IsAttributeFade() const override ;
    virtual bool            IsOrientationFade() const override ;
};

class SdStartPresentationDlg;
class AbstractSdStartPresDlg_Impl : public AbstractSdStartPresDlg
{
private:
    std::unique_ptr<SdStartPresentationDlg> m_xDlg;
public:
    AbstractSdStartPresDlg_Impl(std::unique_ptr<SdStartPresentationDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short   Execute() override;
    virtual void    GetAttr( SfxItemSet& rOutAttrs ) override;
};

class SdPresLayoutDlg;
class AbstractSdPresLayoutDlg_Impl : public AbstractSdPresLayoutDlg
{
    DECL_ABSTDLG_BASE(AbstractSdPresLayoutDlg_Impl,SdPresLayoutDlg)
    virtual void    GetAttr(SfxItemSet& rOutAttrs) override;
};

class SdAbstractSfxDialog_Impl : public SfxAbstractDialog
{
    DECL_ABSTDLG_BASE(SdAbstractSfxDialog_Impl,SfxModalDialog)
    virtual const SfxItemSet*   GetOutputItemSet() const override;
    virtual void        SetText( const OUString& rStr ) override;
};

class SdVectorizeDlg;
class AbstractSdVectorizeDlg_Impl :public AbstractSdVectorizeDlg
{
private:
    std::unique_ptr<SdVectorizeDlg> m_xDlg;
public:
    AbstractSdVectorizeDlg_Impl(std::unique_ptr<SdVectorizeDlg> pDlg)
        : m_xDlg(std::move(pDlg))
    {
    }
    virtual short Execute() override;
    virtual const GDIMetaFile&  GetGDIMetaFile() const override ;
};

class SdPublishingDlg;
class AbstractSdPublishingDlg_Impl :public AbstractSdPublishingDlg
{
    DECL_ABSTDLG_BASE(AbstractSdPublishingDlg_Impl,SdPublishingDlg)
    virtual void GetParameterSequence( css::uno::Sequence< css::beans::PropertyValue >& rParams ) override;
};

class AbstractHeaderFooterDialog_Impl :public AbstractHeaderFooterDialog
{
  DECL_ABSTDLG_BASE(AbstractHeaderFooterDialog_Impl,::sd::HeaderFooterDialog)
};

//AbstractDialogFactory_Impl implementations
class SdAbstractDialogFactory_Impl : public SdAbstractDialogFactory
{

public:
    virtual ~SdAbstractDialogFactory_Impl() {}

    virtual VclPtr<VclAbstractDialog>          CreateBreakDlg(weld::Window* pWindow, ::sd::DrawView* pDrView, ::sd::DrawDocShell* pShell, sal_uLong nSumActionCount, sal_uLong nObjCount) override;
    virtual VclPtr<AbstractCopyDlg>            CreateCopyDlg(vcl::Window* pParent, const SfxItemSet& rInAttrs, ::sd::View* pView) override;
    virtual VclPtr<AbstractSdCustomShowDlg>    CreateSdCustomShowDlg(weld::Window* pParent, SdDrawDocument& rDrawDoc) override;
    virtual VclPtr<SfxAbstractTabDialog>       CreateSdTabCharDialog(vcl::Window* pWindow, const SfxItemSet* pAttr, SfxObjectShell* pDocShell) override;
    virtual VclPtr<SfxAbstractTabDialog>       CreateSdTabPageDialog(vcl::Window* pWindow, const SfxItemSet* pAttr, SfxObjectShell* pDocShell, bool bAreaPage) override;
    virtual VclPtr<AbstractSdModifyFieldDlg>   CreateSdModifyFieldDlg(weld::Window* pWindow, const SvxFieldData* pInField, const SfxItemSet& rSet) override;
    virtual VclPtr<AbstractSdSnapLineDlg>      CreateSdSnapLineDlg(weld::Window* pParent, const SfxItemSet& rInAttrs, ::sd::View* pView) override;
    virtual VclPtr<AbstractSdInsertLayerDlg>   CreateSdInsertLayerDlg(weld::Window* pParent, const SfxItemSet& rInAttrs, bool bDeletable, const OUString& aStr) override;
    virtual VclPtr<AbstractSdInsertPagesObjsDlg> CreateSdInsertPagesObjsDlg(vcl::Window* pParent, const SdDrawDocument* pDoc, SfxMedium* pSfxMedium, const OUString& rFileName ) override;
    virtual VclPtr<AbstractMorphDlg>           CreateMorphDlg(weld::Window* pParent, const SdrObject* pObj1, const SdrObject* pObj2) override;
    virtual VclPtr<SfxAbstractTabDialog>       CreateSdOutlineBulletTabDlg(vcl::Window* pParent, const SfxItemSet* pAttr, ::sd::View* pView) override;
    virtual VclPtr<SfxAbstractTabDialog>       CreateSdParagraphTabDlg(vcl::Window* pParent, const SfxItemSet* pAttr) override;
    virtual VclPtr<AbstractSdStartPresDlg>     CreateSdStartPresentationDlg(weld::Window* pWindow, const SfxItemSet& rInAttrs,
                                                                     const std::vector<OUString> &rPageNames, SdCustomShowList* pCSList ) override;
    virtual VclPtr<VclAbstractDialog>          CreateRemoteDialog( vcl::Window* pWindow ) override; // ad for RemoteDialog
    virtual VclPtr<SfxAbstractTabDialog>       CreateSdPresLayoutTemplateDlg( SfxObjectShell* pDocSh, vcl::Window* pParent, bool bBackgroundDlg, SfxStyleSheetBase& rStyleBase, PresentationObjects ePO, SfxStyleSheetBasePool* pSSPool ) override;
    virtual VclPtr<AbstractSdPresLayoutDlg>    CreateSdPresLayoutDlg( ::sd::DrawDocShell* pDocShell, const SfxItemSet& rInAttrs) override;
    virtual VclPtr<SfxAbstractTabDialog>       CreateSdTabTemplateDlg(vcl::Window* pParent, const SfxObjectShell* pDocShell, SfxStyleSheetBase& rStyleBase, SdrModel* pModel, SdrView* pView ) override;
    virtual VclPtr<SfxAbstractDialog>          CreatSdActionDialog(vcl::Window* pParent, const SfxItemSet* pAttr, ::sd::View* pView) override;
    virtual VclPtr<AbstractSdVectorizeDlg>     CreateSdVectorizeDlg(weld::Window* pParent, const Bitmap& rBmp, ::sd::DrawDocShell* pDocShell) override;
    virtual VclPtr<AbstractSdPublishingDlg>    CreateSdPublishingDlg(vcl::Window* pWindow, DocumentType eDocType) override;

    virtual VclPtr<VclAbstractDialog>          CreateSdPhotoAlbumDialog(weld::Window* pWindow, SdDrawDocument* pDoc) override;

    virtual VclPtr<VclAbstractDialog>          CreateMasterLayoutDialog(weld::Window* pParent, SdDrawDocument* pDoc, SdPage*) override;

    virtual VclPtr<AbstractHeaderFooterDialog> CreateHeaderFooterDialog( sd::ViewShell* pViewShell,
                                                                  vcl::Window* pParent,
                                                                  SdDrawDocument* pDoc,
                                                                  SdPage* pCurrentPage ) override;

    // For TabPage
    virtual CreateTabPage               GetSdOptionsContentsTabPageCreatorFunc() override;
    virtual CreateTabPage               GetSdPrintOptionsTabPageCreatorFunc() override;
    virtual CreateTabPage               GetSdOptionsMiscTabPageCreatorFunc() override;
    virtual CreateTabPage               GetSdOptionsSnapTabPageCreatorFunc() override;

};

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
