object Form1: TForm1
  Left = 20
  Top = 53
  Width = 981
  Height = 666
  Caption = 'Editor de Imagenes'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 16
    Top = 8
    Width = 457
    Height = 281
    Cursor = crCross
    Color = clWhite
    ParentColor = False
    ParentShowHint = False
    ShowHint = False
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
    OnPaint = PaintBox1Paint
  end
  object Label1: TLabel
    Left = 512
    Top = 424
    Width = 57
    Height = 20
    Caption = 'Grosor: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object borrar: TSpeedButton
    Left = 680
    Top = 392
    Width = 65
    Height = 22
    Cursor = crHandPoint
    Caption = 'BORRAR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    OnClick = borrarClick
  end
  object Label2: TLabel
    Left = 456
    Top = 608
    Width = 16
    Height = 24
    Caption = 'X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 952
    Top = 296
    Width = 14
    Height = 24
    Caption = 'Z'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label4: TLabel
    Left = 488
    Top = 0
    Width = 14
    Height = 24
    Caption = 'Y'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 0
    Top = 312
    Width = 14
    Height = 24
    Caption = 'Z'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label6: TLabel
    Left = 456
    Top = 296
    Width = 16
    Height = 24
    Caption = 'X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label7: TLabel
    Left = 0
    Top = 0
    Width = 14
    Height = 24
    Caption = 'Y'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object PaintBox2: TPaintBox
    Left = 504
    Top = 8
    Width = 457
    Height = 281
    Cursor = crCross
    Color = clWhite
    ParentColor = False
    ParentShowHint = False
    ShowHint = False
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
    OnPaint = PaintBox1Paint
  end
  object PaintBox3: TPaintBox
    Left = 16
    Top = 320
    Width = 457
    Height = 281
    Cursor = crCross
    Color = clWhite
    ParentColor = False
    ParentShowHint = False
    ShowHint = False
    OnMouseDown = PaintBox1MouseDown
    OnMouseMove = PaintBox1MouseMove
    OnMouseUp = PaintBox1MouseUp
    OnPaint = PaintBox1Paint
  end
  object Label8: TLabel
    Left = 648
    Top = 424
    Width = 48
    Height = 20
    Caption = 'Lado:  '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 504
    Top = 320
    Width = 249
    Height = 65
    Caption = ' Color '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object InfoClbg: TLabel
      Left = 40
      Top = 32
      Width = 25
      Height = 25
      AutoSize = False
      Color = clWhite
      ParentColor = False
    end
    object InfoClfg: TLabel
      Left = 8
      Top = 32
      Width = 25
      Height = 25
      AutoSize = False
      Color = clBlack
      ParentColor = False
    end
    object CColorGrid1: TCColorGrid
      Left = 72
      Top = 17
      Width = 168
      Height = 40
      GridOrdering = go8x2
      BackgroundIndex = 15
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnChange = CColorGrid1Change
    end
  end
  object ComboBox1: TComboBox
    Left = 512
    Top = 392
    Width = 145
    Height = 24
    DropDownCount = 5
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemHeight = 16
    ParentFont = False
    TabOrder = 0
    Text = ' Estilos'
    OnChange = ComboBox1Change
    Items.Strings = (
      'Linea Continua'
      'Linea Discontinua'
      'Linea Punteada'
      'Linea - Punto'
      'Linea- Punto - Punto')
  end
  object UpDown1: TUpDown
    Left = 608
    Top = 419
    Width = 17
    Height = 30
    Min = 1
    Position = 1
    TabOrder = 2
    Wrap = False
    OnClick = UpDown1Click
  end
  object grosor: TEdit
    Left = 576
    Top = 424
    Width = 25
    Height = 24
    BiDiMode = bdLeftToRight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 2
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 3
    Text = '1'
    OnChange = grosorChange
  end
  object RadioGroup3: TRadioGroup
    Left = 768
    Top = 320
    Width = 89
    Height = 105
    Caption = 'Poligonos '
    Items.Strings = (
      'Crear'
      'Trasladar'
      'Rotar'
      'Escalar'
      'Afilar')
    TabOrder = 4
    OnClick = RadioGroup3Click
  end
  object RadioGroup1: TRadioGroup
    Left = 864
    Top = 320
    Width = 97
    Height = 105
    Caption = 'Figuras '
    Items.Strings = (
      'Piramide'
      'Prisma'
      'Rot. General')
    TabOrder = 5
    OnClick = RadioGroup1Click
  end
  object lados: TEdit
    Left = 696
    Top = 424
    Width = 25
    Height = 24
    BiDiMode = bdLeftToRight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    MaxLength = 2
    ParentBiDiMode = False
    ParentFont = False
    TabOrder = 6
    Text = '3'
    OnChange = ladosChange
  end
  object UpDown2: TUpDown
    Left = 728
    Top = 419
    Width = 17
    Height = 30
    Min = 3
    Position = 3
    TabOrder = 7
    Wrap = False
    OnClick = UpDown2Click
  end
end
