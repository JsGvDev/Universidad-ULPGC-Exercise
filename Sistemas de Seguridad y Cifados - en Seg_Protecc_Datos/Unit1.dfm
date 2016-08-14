object Metodo: TMetodo
  Left = 205
  Top = 124
  Width = 867
  Height = 771
  Caption = 'Metodo'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 48
    Top = 40
    Width = 761
    Height = 137
    HelpType = htKeyword
    Caption = 'Opciones'
    TabOrder = 0
    object eleccion_entrada_datos: TRadioGroup
      Left = 24
      Top = 24
      Width = 329
      Height = 97
      Caption = 'Origen de Datos'
      ItemIndex = 0
      Items.Strings = (
        'Manualmente'
        'Archivo ...')
      TabOrder = 0
      OnClick = eleccion_entrada_datosClick
    end
    object GroupBox2: TGroupBox
      Left = 432
      Top = 24
      Width = 289
      Height = 97
      Caption = 'Metodo de encriptado'
      TabOrder = 1
      object Opciones: TComboBox
        Left = 32
        Top = 32
        Width = 241
        Height = 21
        ItemHeight = 13
        TabOrder = 0
        OnChange = OpcionesChange
        Items.Strings = (
          'Grupo de cinco'
          'Sustituci'#243'n Af'#237'n'
          'Vigen'#232're'
          'Beaufort'
          'Playfair'
          'Transposici'#243'n por grupos'
          'Transposici'#243'n por series'
          'Transposici'#243'n por filas'
          'Transposici'#243'n por columnas')
      end
    end
  end
  object GroupBox3: TGroupBox
    Left = 48
    Top = 200
    Width = 761
    Height = 193
    Caption = 'Introducci'#243'n de texto en claro'
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 123
      Height = 20
      Caption = 'Texto en claro'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 416
      Top = 16
      Width = 108
      Height = 20
      Caption = 'Criptograma'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold, fsItalic]
      ParentFont = False
    end
    object Mensaje_entrada: TMemo
      Left = 16
      Top = 40
      Width = 329
      Height = 137
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 1024
      ParentFont = False
      TabOrder = 0
    end
    object Mensaje_Salida: TMemo
      Left = 416
      Top = 40
      Width = 329
      Height = 137
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      MaxLength = 1024
      ParentFont = False
      TabOrder = 1
    end
  end
  object btnCifrar: TButton
    Left = 112
    Top = 528
    Width = 201
    Height = 73
    Caption = 'Cifrar'
    TabOrder = 2
    OnClick = btnCifrarClick
  end
  object btnDescifrar: TButton
    Left = 512
    Top = 528
    Width = 201
    Height = 73
    Caption = 'Descifrar'
    TabOrder = 3
    OnClick = btnDescifrarClick
  end
  object btnSalir: TButton
    Left = 360
    Top = 544
    Width = 105
    Height = 41
    Caption = 'Salir'
    TabOrder = 4
    OnClick = btnSalirClick
  end
  object SAfin: TGroupBox
    Left = 80
    Top = 408
    Width = 697
    Height = 81
    Caption = 'Par'#225'metros para encriptaci'#243'n af'#237'n'
    TabOrder = 5
    Visible = False
    object Decimacion: TLabel
      Left = 24
      Top = 32
      Width = 142
      Height = 24
      Caption = 'Decimaci'#243'n (a)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Desplazamiento: TLabel
      Left = 264
      Top = 32
      Width = 181
      Height = 24
      Caption = 'Desplazamiento (b)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Modulo: TLabel
      Left = 544
      Top = 32
      Width = 71
      Height = 24
      Caption = 'M'#243'dulo'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object textDeci: TEdit
      Left = 176
      Top = 32
      Width = 49
      Height = 32
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = '1'
      OnExit = textDeciExit
    end
    object textDespla: TEdit
      Left = 456
      Top = 32
      Width = 49
      Height = 32
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = '0'
      OnExit = textDesplaExit
    end
    object textMod: TEdit
      Left = 632
      Top = 32
      Width = 49
      Height = 32
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Text = '27'
    end
  end
  object Vigenere: TGroupBox
    Left = 96
    Top = 424
    Width = 665
    Height = 57
    Caption = 'Clave Vigen'#232're'
    TabOrder = 6
    Visible = False
    object Label3: TLabel
      Left = 8
      Top = 16
      Width = 53
      Height = 24
      Caption = 'Clave'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object textclavevige: TEdit
      Left = 72
      Top = 16
      Width = 577
      Height = 32
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
  end
  object Beaufort: TGroupBox
    Left = 96
    Top = 424
    Width = 665
    Height = 57
    Caption = 'Clave Beaufort'
    TabOrder = 7
    Visible = False
    object Label4: TLabel
      Left = 8
      Top = 16
      Width = 53
      Height = 24
      Caption = 'Clave'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object textclavebeauf: TEdit
      Left = 72
      Top = 16
      Width = 577
      Height = 32
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
  end
  object Playfair: TGroupBox
    Left = 96
    Top = 424
    Width = 665
    Height = 57
    Caption = 'Clave Playfair'
    TabOrder = 8
    Visible = False
    object Label5: TLabel
      Left = 8
      Top = 16
      Width = 53
      Height = 24
      Caption = 'Clave'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object textclaveplay: TEdit
      Left = 72
      Top = 16
      Width = 577
      Height = 32
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
  end
  object Grupos: TGroupBox
    Left = 96
    Top = 424
    Width = 665
    Height = 57
    Caption = 'Clave por grupos'
    TabOrder = 9
    Visible = False
    object Label6: TLabel
      Left = 8
      Top = 16
      Width = 53
      Height = 24
      Caption = 'Clave'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object textclavegrupos: TEdit
      Left = 72
      Top = 16
      Width = 577
      Height = 32
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
  end
  object Series: TGroupBox
    Left = 80
    Top = 408
    Width = 697
    Height = 105
    Caption = 'Par'#225'metros para transposici'#243'n por series'
    TabOrder = 10
    Visible = False
    object Label7: TLabel
      Left = 32
      Top = 24
      Width = 296
      Height = 13
      Caption = 'Para codificar se utilizar'#225'n las siguientes funciones:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 16
      Top = 56
      Width = 668
      Height = 16
      Caption = 
        'N'#250'merosros Primos                                               ' +
        '          N'#250'meros pares                                         ' +
        '              Resto de N'#250'meros'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsItalic]
      ParentFont = False
    end
  end
  object Filas: TGroupBox
    Left = 80
    Top = 416
    Width = 697
    Height = 89
    Caption = 'Par'#225'metros para transposici'#243'n por filas'
    TabOrder = 11
    Visible = False
    object Label9: TLabel
      Left = 16
      Top = 32
      Width = 119
      Height = 16
      Caption = 'N'#250'mero de Filas:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Num_filas: TEdit
      Left = 144
      Top = 24
      Width = 529
      Height = 21
      TabOrder = 0
    end
  end
  object Columnas: TGroupBox
    Left = 80
    Top = 416
    Width = 697
    Height = 89
    Caption = 'Par'#225'metros para transposici'#243'n por columnas'
    TabOrder = 12
    Visible = False
    object Label10: TLabel
      Left = 16
      Top = 32
      Width = 153
      Height = 16
      Caption = 'N'#250'mero de Columnas:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Num_col: TEdit
      Left = 176
      Top = 24
      Width = 489
      Height = 21
      TabOrder = 0
    end
  end
  object Fichero: TGroupBox
    Left = 96
    Top = 256
    Width = 633
    Height = 113
    Caption = 'Fichero'
    TabOrder = 13
    Visible = False
    object Label11: TLabel
      Left = 48
      Top = 56
      Width = 38
      Height = 13
      Caption = 'Label11'
      Visible = False
    end
    object Label12: TLabel
      Left = 48
      Top = 80
      Width = 38
      Height = 13
      Caption = 'Label12'
      Visible = False
    end
    object Abrefichero: TButton
      Left = 80
      Top = 16
      Width = 481
      Height = 33
      Caption = 'Abrir fichero'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = AbreficheroClick
    end
  end
  object Abre: TOpenDialog
    Left = 320
    Top = 552
  end
  object Guardar: TSaveDialog
    Left = 472
    Top = 552
  end
end
