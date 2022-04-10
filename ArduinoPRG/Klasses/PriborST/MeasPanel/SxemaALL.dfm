object FormSH: TFormSH
  Left = 0
  Top = 0
  Caption = #1057#1074#1086#1081#1089#1090#1074#1072
  ClientHeight = 610
  ClientWidth = 797
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    797
    610)
  PixelsPerInch = 96
  TextHeight = 13
  object AdvPageControl1: TAdvPageControl
    Left = 8
    Top = 2
    Width = 777
    Height = 575
    ActivePage = AdvTabSheet1
    ActiveFont.Charset = DEFAULT_CHARSET
    ActiveFont.Color = clWindowText
    ActiveFont.Height = -11
    ActiveFont.Name = 'Tahoma'
    ActiveFont.Style = []
    DoubleBuffered = True
    TabBackGroundColor = clBtnFace
    TabMargin.RightMargin = 0
    TabOverlap = 0
    Version = '2.0.0.10'
    PersistPagesState.Location = plRegistry
    PersistPagesState.Enabled = False
    TabOrder = 0
    object AdvTabSheet1: TAdvTabSheet
      Caption = #1057#1093#1077#1084#1072' '
      Color = clBtnFace
      ColorTo = clNone
      TabColor = clBtnFace
      TabColorTo = clNone
      object Label9: TLabel
        Left = 13
        Top = 3
        Width = 119
        Height = 13
        Caption = #1064#1083#1102#1079' USB/LAN/GPIB IP:'
      end
      object W7Image1: TW7Image
        Left = 441
        Top = 46
        Width = 216
        Height = 147
        ParentFont = False
      end
      object Label1: TLabel
        Left = 44
        Top = 501
        Width = 130
        Height = 13
        Caption = #1048#1089#1090#1086#1095#1085#1080#1082' '#1087#1080#1090#1072#1085#1080#1103' '#1058'6700:'
      end
      object Label12: TLabel
        Left = 10
        Top = 49
        Width = 60
        Height = 13
        Caption = #1040#1085#1072#1083#1080#1079#1072#1090#1086#1088
      end
      object W7Image2: TW7Image
        Left = 441
        Top = 199
        Width = 216
        Height = 129
        ParentFont = False
      end
      object Label11: TLabel
        Left = 57
        Top = 362
        Width = 133
        Height = 13
        Caption = #1040#1085#1072#1083#1080#1079#1072#1090#1086#1088' '#1094#1077#1087#1077#1081' Agilent:'
      end
      object Label13: TLabel
        Left = 132
        Top = 339
        Width = 58
        Height = 13
        Caption = #1043#1077#1085#1077#1088#1072#1090#1086#1088':'
      end
      object Label8: TLabel
        Left = 85
        Top = 387
        Width = 105
        Height = 13
        Caption = #1050#1086#1084#1084#1091#1090#1072#1090#1086#1088' 34980A:'
      end
      object Label2: TLabel
        Left = 68
        Top = 414
        Width = 121
        Height = 13
        Caption = #1055#1077#1088#1077#1082#1083#1102#1095#1077#1085#1080#1077' '#1082#1072#1085#1072#1083#1086#1074
      end
      object W7Image3: TW7Image
        Left = 441
        Top = 334
        Width = 216
        Height = 71
        ParentFont = False
      end
      object W7Image4: TW7Image
        Left = 442
        Top = 411
        Width = 215
        Height = 78
        ParentFont = False
      end
      object W7Image5: TW7Image
        Left = 441
        Top = 495
        Width = 216
        Height = 26
        ParentFont = False
      end
      object W7Image6: TW7Image
        Left = 354
        Top = 46
        Width = 81
        Height = 475
        ParentFont = False
      end
      object W7Image7: TW7Image
        Left = 354
        Top = 3
        Width = 81
        Height = 37
        ParentFont = False
      end
      object W7Image8: TW7Image
        Left = 441
        Top = 3
        Width = 303
        Height = 37
        ParentFont = False
      end
      object W7Image9: TW7Image
        Left = 663
        Top = 46
        Width = 81
        Height = 475
        ParentFont = False
      end
      object Label17: TLabel
        Left = 456
        Top = 168
        Width = 10
        Height = 13
        Caption = 'Er'
      end
      object EditIP: TEdit
        Left = 253
        Top = 3
        Width = 86
        Height = 21
        TabOrder = 0
        Text = '10.29.31.160'
      end
      object ComboBPN6700: TComboBox
        Left = 180
        Top = 498
        Width = 60
        Height = 21
        ItemIndex = 1
        TabOrder = 1
        Text = '   GPIB:'
        OnChange = ComboBPN6700Change
        Items.Strings = (
          'LAN IP:'
          '   GPIB:'
          '')
      end
      object EditBPadr: TEdit
        Left = 259
        Top = 499
        Width = 86
        Height = 21
        TabOrder = 2
        Text = '15'
      end
      object ComboBox1: TComboBox
        Left = 76
        Top = 46
        Width = 106
        Height = 21
        ItemIndex = 0
        TabOrder = 3
        Text = 'Agilent  8560EC'
        OnChange = ComboBox1Change
        Items.Strings = (
          'Agilent  8560EC'
          'Agilent  N9030A'
          'R&S FSU50'
          'R&S FSL18'
          'Keysight E4407'
          'Keysight N9020B')
      end
      object ComboBox3: TComboBox
        Left = 190
        Top = 46
        Width = 60
        Height = 21
        ItemIndex = 0
        TabOrder = 4
        Text = 'LAN IP:'
        OnChange = ComboBox3Change
        Items.Strings = (
          'LAN IP:'
          '   GPIB:'
          '')
      end
      object Edit1: TEdit
        Left = 253
        Top = 46
        Width = 86
        Height = 21
        TabOrder = 5
        Text = '20'
      end
      object GroupBox1: TGroupBox
        Left = 13
        Top = 199
        Width = 335
        Height = 75
        BiDiMode = bdLeftToRight
        Caption = #1043#1077#1090#1077#1088#1086#1076#1080#1085#1099
        Color = clCream
        Ctl3D = True
        ParentBackground = False
        ParentBiDiMode = False
        ParentColor = False
        ParentCtl3D = False
        TabOrder = 6
        object Label14: TLabel
          Left = 3
          Top = 21
          Width = 61
          Height = 13
          Caption = #1043#1077#1090#1077#1088#1086#1076#1080#1085'1'
        end
        object Label15: TLabel
          Left = 3
          Top = 49
          Width = 61
          Height = 13
          Caption = #1043#1077#1090#1077#1088#1086#1076#1080#1085'2'
        end
        object Label16: TLabel
          Left = 73
          Top = 49
          Width = 75
          Height = 13
          Caption = 'Agilent  E4426B'
        end
        object Edit9: TEdit
          Left = 246
          Top = 45
          Width = 86
          Height = 21
          TabOrder = 0
          Text = '22'
        end
        object Edit8: TEdit
          Left = 246
          Top = 18
          Width = 86
          Height = 21
          TabOrder = 1
          Text = '17'
        end
        object ComboBox2: TComboBox
          Left = 70
          Top = 18
          Width = 107
          Height = 21
          ItemIndex = 2
          TabOrder = 2
          Text = 'Agilent  N5183A'
          OnChange = ComboBox2Change
          Items.Strings = (
            'Agilent  E4425B'
            'R&S     SMU200 A'
            'Agilent  N5183A')
        end
        object cbb1: TComboBox
          Left = 183
          Top = 18
          Width = 60
          Height = 21
          ItemIndex = 1
          TabOrder = 3
          Text = '   GPIB:'
          OnChange = ComboBox2Change
          Items.Strings = (
            'LAN IP:'
            '   GPIB:'
            '')
        end
        object cbb2: TComboBox
          Left = 183
          Top = 45
          Width = 60
          Height = 21
          ItemIndex = 1
          TabOrder = 4
          Text = '   GPIB:'
          OnChange = ComboBox2Change
          Items.Strings = (
            'LAN IP:'
            '   GPIB:'
            ''
            '')
        end
      end
      object cbb3: TComboBox
        Left = 196
        Top = 335
        Width = 60
        Height = 21
        ItemIndex = 1
        TabOrder = 7
        Text = '   GPIB:'
        OnChange = cbb3Change
        Items.Strings = (
          'LAN IP:'
          '   GPIB:'
          '')
      end
      object cbb4: TComboBox
        Left = 196
        Top = 360
        Width = 60
        Height = 21
        ItemIndex = 1
        TabOrder = 8
        Text = '   GPIB:'
        OnChange = cbb4Change
        Items.Strings = (
          'LAN IP:'
          '   GPIB:'
          '')
      end
      object cbb5: TComboBox
        Left = 196
        Top = 384
        Width = 60
        Height = 21
        ItemIndex = 1
        TabOrder = 9
        Text = '   GPIB:'
        OnChange = cbb5Change
        Items.Strings = (
          'LAN IP:'
          '   GPIB:'
          '')
      end
      object Edit10: TEdit
        Left = 259
        Top = 360
        Width = 86
        Height = 21
        TabOrder = 10
        Text = '25'
      end
      object Edit11: TEdit
        Left = 259
        Top = 335
        Width = 86
        Height = 21
        TabOrder = 11
        Text = '19'
      end
      object Edit7: TEdit
        Left = 259
        Top = 384
        Width = 86
        Height = 21
        TabOrder = 12
        Text = '15'
      end
      object ComboBox16: TComboBox
        Left = 195
        Top = 411
        Width = 109
        Height = 21
        ItemIndex = 0
        TabOrder = 13
        Text = #1056#1091#1095#1085#1086#1077
        OnChange = ComboBox16Change
        Items.Strings = (
          #1056#1091#1095#1085#1086#1077
          #1050#1086#1084#1091#1090#1072#1090#1086#1088' 8 '#1082
          #1050#1086#1084#1091#1090#1072#1090#1086#1088' 16 '#1082
          #1050#1086#1084#1091#1090#1072#1090#1086#1088' 16'#1082' '#1042#1063)
      end
      object Button2: TButton
        Left = 441
        Top = 527
        Width = 75
        Height = 25
        Caption = 'Button2'
        TabOrder = 14
        OnClick = Button2Click
      end
    end
    object Настройки: TAdvTabSheet
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      Color = clBtnFace
      ColorTo = clNone
      TabColor = clBtnFace
      TabColorTo = clNone
      object Label3: TLabel
        Left = 146
        Top = 261
        Width = 24
        Height = 13
        Caption = 'POW'
      end
      object Label4: TLabel
        Left = 198
        Top = 261
        Width = 27
        Height = 13
        Caption = 'RLWL'
      end
      object Label5: TLabel
        Left = 241
        Top = 261
        Width = 47
        Height = 13
        Caption = 'RLWL10M'
      end
      object Label6: TLabel
        Left = 303
        Top = 261
        Width = 24
        Height = 13
        Caption = 'Span'
      end
      object Label7: TLabel
        Left = 355
        Top = 261
        Width = 23
        Height = 13
        Caption = 'RBW'
      end
      object Label18: TLabel
        Left = 408
        Top = 261
        Width = 21
        Height = 13
        Caption = 'Fofs'
      end
      object Edit2: TEdit
        Left = 138
        Top = 277
        Width = 45
        Height = 21
        TabOrder = 0
        Text = '-50'
      end
      object Edit3: TEdit
        Left = 190
        Top = 277
        Width = 45
        Height = 21
        TabOrder = 1
        Text = '-20'
      end
      object Edit4: TEdit
        Left = 242
        Top = 277
        Width = 45
        Height = 21
        TabOrder = 2
        Text = '10'
      end
      object Edit5: TEdit
        Left = 294
        Top = 277
        Width = 45
        Height = 21
        TabOrder = 3
        Text = '0,1'
      end
      object Edit6: TEdit
        Left = 346
        Top = 277
        Width = 45
        Height = 21
        TabOrder = 4
        Text = '3000'
      end
      object Edit12: TEdit
        Left = 399
        Top = 277
        Width = 45
        Height = 21
        TabOrder = 5
        Text = '100'
      end
    end
    object Калибровка: TAdvTabSheet
      Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072
      Color = clBtnFace
      ColorTo = clNone
      TabColor = clBtnFace
      TabColorTo = clNone
      object Label10: TLabel
        Left = 48
        Top = 3
        Width = 61
        Height = 13
        Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1082#1072
      end
      object AdvStringGrid1: TAdvStringGrid
        Left = 16
        Top = 22
        Width = 129
        Height = 119
        Cursor = crDefault
        ColCount = 2
        DrawingStyle = gdsClassic
        RowCount = 5
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
        ScrollBars = ssBoth
        TabOrder = 0
        HoverRowCells = [hcNormal, hcSelected]
        ActiveCellFont.Charset = DEFAULT_CHARSET
        ActiveCellFont.Color = clWindowText
        ActiveCellFont.Height = -11
        ActiveCellFont.Name = 'Tahoma'
        ActiveCellFont.Style = [fsBold]
        ControlLook.FixedGradientHoverFrom = clGray
        ControlLook.FixedGradientHoverTo = clWhite
        ControlLook.FixedGradientDownFrom = clGray
        ControlLook.FixedGradientDownTo = clSilver
        ControlLook.DropDownHeader.Font.Charset = DEFAULT_CHARSET
        ControlLook.DropDownHeader.Font.Color = clWindowText
        ControlLook.DropDownHeader.Font.Height = -11
        ControlLook.DropDownHeader.Font.Name = 'Tahoma'
        ControlLook.DropDownHeader.Font.Style = []
        ControlLook.DropDownHeader.Visible = True
        ControlLook.DropDownHeader.Buttons = <>
        ControlLook.DropDownFooter.Font.Charset = DEFAULT_CHARSET
        ControlLook.DropDownFooter.Font.Color = clWindowText
        ControlLook.DropDownFooter.Font.Height = -11
        ControlLook.DropDownFooter.Font.Name = 'Tahoma'
        ControlLook.DropDownFooter.Font.Style = []
        ControlLook.DropDownFooter.Visible = True
        ControlLook.DropDownFooter.Buttons = <>
        Filter = <>
        FilterDropDown.Font.Charset = DEFAULT_CHARSET
        FilterDropDown.Font.Color = clWindowText
        FilterDropDown.Font.Height = -11
        FilterDropDown.Font.Name = 'Tahoma'
        FilterDropDown.Font.Style = []
        FilterDropDown.TextChecked = 'Checked'
        FilterDropDown.TextUnChecked = 'Unchecked'
        FilterDropDownClear = '(All)'
        FilterEdit.TypeNames.Strings = (
          'Starts with'
          'Ends with'
          'Contains'
          'Not contains'
          'Equal'
          'Not equal'
          'Clear')
        FixedRowHeight = 22
        FixedFont.Charset = DEFAULT_CHARSET
        FixedFont.Color = clWindowText
        FixedFont.Height = -11
        FixedFont.Name = 'Tahoma'
        FixedFont.Style = [fsBold]
        FloatFormat = '%.2f'
        HoverButtons.Buttons = <>
        HoverButtons.Position = hbLeftFromColumnLeft
        HTMLSettings.ImageFolder = 'images'
        HTMLSettings.ImageBaseName = 'img'
        PrintSettings.DateFormat = 'dd/mm/yyyy'
        PrintSettings.Font.Charset = DEFAULT_CHARSET
        PrintSettings.Font.Color = clWindowText
        PrintSettings.Font.Height = -11
        PrintSettings.Font.Name = 'Tahoma'
        PrintSettings.Font.Style = []
        PrintSettings.FixedFont.Charset = DEFAULT_CHARSET
        PrintSettings.FixedFont.Color = clWindowText
        PrintSettings.FixedFont.Height = -11
        PrintSettings.FixedFont.Name = 'Tahoma'
        PrintSettings.FixedFont.Style = []
        PrintSettings.HeaderFont.Charset = DEFAULT_CHARSET
        PrintSettings.HeaderFont.Color = clWindowText
        PrintSettings.HeaderFont.Height = -11
        PrintSettings.HeaderFont.Name = 'Tahoma'
        PrintSettings.HeaderFont.Style = []
        PrintSettings.FooterFont.Charset = DEFAULT_CHARSET
        PrintSettings.FooterFont.Color = clWindowText
        PrintSettings.FooterFont.Height = -11
        PrintSettings.FooterFont.Name = 'Tahoma'
        PrintSettings.FooterFont.Style = []
        PrintSettings.PageNumSep = '/'
        SearchFooter.FindNextCaption = 'Find &next'
        SearchFooter.FindPrevCaption = 'Find &previous'
        SearchFooter.Font.Charset = DEFAULT_CHARSET
        SearchFooter.Font.Color = clWindowText
        SearchFooter.Font.Height = -11
        SearchFooter.Font.Name = 'Tahoma'
        SearchFooter.Font.Style = []
        SearchFooter.HighLightCaption = 'Highlight'
        SearchFooter.HintClose = 'Close'
        SearchFooter.HintFindNext = 'Find next occurrence'
        SearchFooter.HintFindPrev = 'Find previous occurrence'
        SearchFooter.HintHighlight = 'Highlight occurrences'
        SearchFooter.MatchCaseCaption = 'Match case'
        ShowDesignHelper = False
        SortSettings.DefaultFormat = ssAutomatic
        URLEdit = True
        Version = '8.1.3.0'
        ColWidths = (
          64
          64)
        RowHeights = (
          22
          23
          22
          22
          22)
      end
    end
  end
  object Button1: TButton
    Left = 8
    Top = 583
    Width = 75
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
    TabOrder = 1
    OnClick = Button1Click
  end
end
