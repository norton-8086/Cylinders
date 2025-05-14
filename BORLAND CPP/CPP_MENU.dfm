object MENU: TMENU
  Left = 0
  Top = 0
  Caption = 'MENU'
  ClientHeight = 393
  ClientWidth = 485
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 23
    Top = 32
    Width = 390
    Height = 13
    Caption = #1042#1042#1045#1044#1048#1058#1045' '#1048#1053#1060#1054#1056#1052#1040#1062#1048#1070' '#1054' '#1055#1040#1056#1045' '#1062#1048#1051#1048#1053#1044#1056#1054#1042' '#1048' '#1042#1067#1041#1045#1056#1048#1058#1045' '#1057#1055#1054#1057#1054#1041' '#1056#1040#1057#1063#1025#1058#1040
  end
  object Label2: TLabel
    Left = 156
    Top = 51
    Width = 51
    Height = 13
    Caption = 'Cylinder_1'
  end
  object Label3: TLabel
    Left = 327
    Top = 51
    Width = 51
    Height = 13
    Caption = 'Cylinder_2'
  end
  object Label4: TLabel
    Left = 38
    Top = 75
    Width = 31
    Height = 13
    Caption = #1047#1072#1088#1103#1076
  end
  object Label5: TLabel
    Left = 35
    Top = 102
    Width = 36
    Height = 13
    Caption = #1056#1072#1076#1080#1091#1089
  end
  object Label6: TLabel
    Left = 37
    Top = 128
    Width = 32
    Height = 13
    Caption = #1044#1083#1080#1085#1072
  end
  object Label7: TLabel
    Left = 7
    Top = 155
    Width = 93
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1082#1086#1083#1077#1094
  end
  object Label8: TLabel
    Left = 184
    Top = 200
    Width = 93
    Height = 13
    Caption = #1052#1045#1058#1054#1044#1067' '#1056#1040#1057#1063#1025#1058#1040
  end
  object Label9: TLabel
    Left = 67
    Top = 224
    Width = 100
    Height = 13
    Caption = #1043#1088#1072#1076#1080#1077#1085#1090#1085#1099#1081' '#1089#1087#1091#1089#1082
  end
  object Label10: TLabel
    Left = 292
    Top = 224
    Width = 49
    Height = 13
    Caption = #1055#1088#1086#1095#1077#1077
  end
  object Grad_W: TButton
    Left = 80
    Top = 256
    Width = 75
    Height = 25
    Caption = #1069#1085#1077#1088#1075#1080#1103
    TabOrder = 0
    OnClick = Grad_WClick
  end
  object Grad_fi: TButton
    Left = 80
    Top = 287
    Width = 75
    Height = 25
    Caption = #1055#1086#1090#1077#1085#1094#1080#1072#1083
    TabOrder = 1
    OnClick = Grad_fiClick
  end
  object Grad_E: TButton
    Left = 80
    Top = 318
    Width = 75
    Height = 25
    Caption = #1055#1086#1083#1077
    TabOrder = 2
    OnClick = Grad_EClick
  end
  object SLAU_fi: TButton
    Left = 208
    Top = 287
    Width = 203
    Height = 25
    Caption = #1052#1077#1090#1086#1076' '#1084#1085#1086#1078#1080#1090#1077#1083#1077#1081' '#1051#1072#1075#1088#1072#1085#1078#1072
    TabOrder = 3
    OnClick = SLAU_fiClick
  end
  object SLAU_E: TButton
    Left = 208
    Top = 318
    Width = 203
    Height = 25
    Caption = #1055#1086#1083#1077' c '#1091#1095#1105#1090#1086#1084' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1103' '#1079#1072#1088#1103#1076#1072
    TabOrder = 4
    OnClick = SLAU_EClick
  end
  object Ohm: TButton
    Left = 272
    Top = 256
    Width = 75
    Height = 25
    Caption = 'Ohm'
    TabOrder = 5
    OnClick = OhmClick
  end
  object Qtotal_1: TEdit
    Left = 128
    Top = 71
    Width = 121
    Height = 21
    TabOrder = 6
    Text = '0'
  end
  object R_1: TEdit
    Left = 128
    Top = 98
    Width = 121
    Height = 21
    TabOrder = 7
    Text = '1'
  end
  object L_1: TEdit
    Left = 128
    Top = 124
    Width = 121
    Height = 21
    TabOrder = 8
    Text = '1'
  end
  object N_1: TEdit
    Left = 128
    Top = 151
    Width = 121
    Height = 21
    TabOrder = 9
    Text = '1000'
  end
  object Qtotal_2: TEdit
    Left = 292
    Top = 71
    Width = 121
    Height = 21
    TabOrder = 10
    Text = '1'
  end
  object R_2: TEdit
    Left = 292
    Top = 98
    Width = 121
    Height = 21
    TabOrder = 11
    Text = '0,01'
  end
  object L_2: TEdit
    Left = 292
    Top = 124
    Width = 121
    Height = 21
    TabOrder = 12
    Text = '0,01'
  end
  object N_2: TEdit
    Left = 292
    Top = 151
    Width = 121
    Height = 21
    TabOrder = 13
    Text = '1000'
  end
end
