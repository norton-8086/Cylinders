object Ohm_Window: TOhm_Window
  Left = 0
  Top = 0
  Caption = 'Ohm_Window'
  ClientHeight = 823
  ClientWidth = 1178
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 164
    Top = 19
    Width = 51
    Height = 13
    Caption = 'Cylinder_1'
  end
  object Label3: TLabel
    Left = 335
    Top = 19
    Width = 51
    Height = 13
    Caption = 'Cylinder_2'
  end
  object Label4: TLabel
    Left = 46
    Top = 43
    Width = 31
    Height = 13
    Caption = #1047#1072#1088#1103#1076
  end
  object Label5: TLabel
    Left = 43
    Top = 70
    Width = 36
    Height = 13
    Caption = #1056#1072#1076#1080#1091#1089
  end
  object Label6: TLabel
    Left = 45
    Top = 96
    Width = 32
    Height = 13
    Caption = #1044#1083#1080#1085#1072
  end
  object Label7: TLabel
    Left = 15
    Top = 123
    Width = 93
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1082#1086#1083#1077#1094
  end
  object Label11: TLabel
    Left = 512
    Top = 19
    Width = 61
    Height = 13
    Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
  end
  object Label12: TLabel
    Left = 684
    Top = 68
    Width = 36
    Height = 13
    Caption = 'W_now'
  end
  object Label13: TLabel
    Left = 686
    Top = 95
    Width = 33
    Height = 13
    Caption = 'Dev_Fi'
  end
  object Label14: TLabel
    Left = 687
    Top = 122
    Width = 31
    Height = 13
    Caption = 'Dev_E'
  end
  object Label15: TLabel
    Left = 680
    Top = 41
    Width = 45
    Height = 13
    Caption = 'W_article'
  end
  object Label16: TLabel
    Left = 932
    Top = 69
    Width = 42
    Height = 13
    Caption = 'Qtotal_2'
  end
  object Label17: TLabel
    Left = 943
    Top = 96
    Width = 20
    Height = 13
    Caption = 'Fi_1'
  end
  object Label18: TLabel
    Left = 943
    Top = 123
    Width = 20
    Height = 13
    Caption = 'Fi_2'
  end
  object Label19: TLabel
    Left = 932
    Top = 42
    Width = 42
    Height = 13
    Caption = 'Qtotal_1'
  end
  object TLabel
    Left = 784
    Top = 160
    Width = 109
    Height = 13
    Caption = #1069#1085#1077#1088#1075#1080#1103' '#1085#1072' '#1091#1076#1072#1083#1077#1085#1080#1080
  end
  object Label1: TLabel
    Left = 943
    Top = 160
    Width = 29
    Height = 13
    Caption = 'Resist'
  end
  object Qtotal_1: TEdit
    Left = 136
    Top = 39
    Width = 121
    Height = 21
    TabOrder = 0
    Text = '1'
  end
  object R_1: TEdit
    Left = 136
    Top = 66
    Width = 121
    Height = 21
    TabOrder = 1
    Text = '1'
  end
  object L_1: TEdit
    Left = 136
    Top = 92
    Width = 121
    Height = 21
    TabOrder = 2
    Text = '1'
  end
  object N_1: TEdit
    Left = 136
    Top = 119
    Width = 121
    Height = 21
    TabOrder = 3
    Text = '100'
  end
  object Qtotal_2: TEdit
    Left = 300
    Top = 39
    Width = 121
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object R_2: TEdit
    Left = 300
    Top = 66
    Width = 121
    Height = 21
    TabOrder = 5
    Text = '1'
  end
  object L_2: TEdit
    Left = 300
    Top = 92
    Width = 121
    Height = 21
    TabOrder = 6
    Text = '1'
  end
  object N_2: TEdit
    Left = 300
    Top = 119
    Width = 121
    Height = 21
    TabOrder = 7
    Text = '100'
  end
  object W_now: TEdit
    Left = 752
    Top = 65
    Width = 121
    Height = 21
    TabOrder = 8
  end
  object Dev_Fi: TEdit
    Left = 752
    Top = 92
    Width = 121
    Height = 21
    TabOrder = 9
  end
  object Dev_E: TEdit
    Left = 752
    Top = 119
    Width = 121
    Height = 21
    TabOrder = 10
  end
  object W_article: TEdit
    Left = 752
    Top = 38
    Width = 121
    Height = 21
    TabOrder = 11
  end
  object Q_2_now: TEdit
    Left = 1000
    Top = 65
    Width = 121
    Height = 21
    TabOrder = 12
  end
  object Fi_1_now: TEdit
    Left = 1000
    Top = 92
    Width = 121
    Height = 21
    TabOrder = 13
  end
  object Fi_2_now: TEdit
    Left = 1000
    Top = 119
    Width = 121
    Height = 21
    TabOrder = 14
  end
  object Q_1_now: TEdit
    Left = 1000
    Top = 38
    Width = 121
    Height = 21
    TabOrder = 15
  end
  object Command: TEdit
    Left = 488
    Top = 38
    Width = 105
    Height = 21
    TabOrder = 16
  end
  object Start: TButton
    Left = 498
    Top = 110
    Width = 75
    Height = 25
    Caption = 'START'
    TabOrder = 17
    OnClick = StartClick
  end
  object Q_1: TListBox
    Left = 41
    Top = 264
    Width = 489
    Height = 241
    ItemHeight = 13
    TabOrder = 18
  end
  object Fi_1: TListBox
    Left = 40
    Top = 536
    Width = 490
    Height = 241
    ItemHeight = 13
    TabOrder = 19
  end
  object Q_2: TListBox
    Left = 647
    Top = 264
    Width = 490
    Height = 241
    ItemHeight = 13
    TabOrder = 20
  end
  object Fi_2: TListBox
    Left = 647
    Top = 536
    Width = 490
    Height = 241
    ItemHeight = 13
    TabOrder = 21
  end
  object Resist: TEdit
    Left = 1000
    Top = 157
    Width = 121
    Height = 21
    TabOrder = 22
  end
end
