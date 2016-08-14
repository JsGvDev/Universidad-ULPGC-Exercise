object Form1: TForm1
  Left = 60
  Top = 56
  Width = 928
  Height = 673
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
    Left = 8
    Top = 8
    Width = 905
    Height = 529
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
    Left = 280
    Top = 600
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
    Left = 424
    Top = 568
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
  object RadioGroup1: TRadioGroup
    Left = 496
    Top = 560
    Width = 81
    Height = 73
    Caption = 'Interno '
    Items.Strings = (
      'L'#237'nea'
      'Elipse'
      'C'#237'rculo')
    TabOrder = 1
    OnClick = RadioGroup1Click
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 560
    Width = 249
    Height = 65
    Caption = ' Color '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
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
      Top = 25
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
    Left = 272
    Top = 568
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
    Left = 400
    Top = 595
    Width = 17
    Height = 30
    Min = 1
    Position = 1
    TabOrder = 3
    Wrap = False
    OnClick = UpDown1Click
  end
  object grosor: TEdit
    Left = 360
    Top = 600
    Width = 33
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
    TabOrder = 4
    Text = '1'
    OnChange = grosorChange
  end
  object CheckBox1: TCheckBox
    Left = 424
    Top = 600
    Width = 65
    Height = 25
    Caption = 'Solido'
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 5
    OnClick = CheckBox1Click
  end
  object RadioGroup2: TRadioGroup
    Left = 584
    Top = 560
    Width = 89
    Height = 73
    Caption = 'Algoritmos '
    Items.Strings = (
      'Bresenham'
      'C'#237'rculoPM'
      'Relleno')
    TabOrder = 6
    OnClick = RadioGroup2Click
  end
  object RadioGroup3: TRadioGroup
    Left = 680
    Top = 560
    Width = 89
    Height = 73
    Caption = 'Poligonos '
    Items.Strings = (
      'Crear'
      'Trasladar'
      'Rotar'
      'Escalar')
    TabOrder = 7
    OnClick = RadioGroup3Click
  end
  object RadioGroup4: TRadioGroup
    Left = 776
    Top = 560
    Width = 81
    Height = 49
    Caption = 'Opcion Pol '
    Items.Strings = (
      'Reflexion'
      'Afilar')
    TabOrder = 8
    OnClick = RadioGroup4Click
  end
  object CheckBox2: TCheckBox
    Left = 784
    Top = 616
    Width = 65
    Height = 17
    Caption = 'Recorte'
    TabOrder = 9
    OnClick = CheckBox2Click
  end
end
