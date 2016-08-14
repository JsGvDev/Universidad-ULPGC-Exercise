object Form1: TForm1
  Left = 122
  Top = 29
  Width = 967
  Height = 689
  Caption = 'Navegador 3D'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 288
    Top = 8
    Width = 337
    Height = 24
    Alignment = taCenter
    AutoSize = False
    Caption = 'VISTA DESDE EL F1_1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 568
    Top = 16
    Width = 65
    Height = 13
    Caption = 'Velocidad --> '
  end
  object PanelVista: TOpenGL
    Left = 8
    Top = 144
    Width = 1009
    Height = 544
    GLFlags = [f_DOUBLEBUFFER, f_DRAW_TO_WINDOW, f_SUPPORT_OPENGL]
    PixelsPerInch = 96
    TabOrder = 2
    OnResize = PanelVistaResize
    OnGLPaint = PanelVistaPaint
    OnGLInit = PanelVistaGLInit
  end
  object PanelRadar: TOpenGL
    Left = 760
    Top = 8
    Width = 256
    Height = 256
    GLFlags = [f_DOUBLEBUFFER, f_DRAW_TO_WINDOW, f_SUPPORT_OPENGL]
    PixelsPerInch = 96
    TabOrder = 1
    OnResize = PanelRadarResize
    OnGLPaint = PanelRadarPaint
    OnGLInit = PanelRadarGLInit
  end
  object PanelBrujula: TOpenGL
    Left = 8
    Top = 8
    Width = 128
    Height = 128
    GLFlags = [f_DOUBLEBUFFER, f_DRAW_TO_WINDOW, f_SUPPORT_OPENGL]
    PixelsPerInch = 96
    TabOrder = 0
    OnResize = PanelBrujulaResize
    OnGLPaint = PanelBrujulaPaint
    OnGLInit = PanelBrujulaGLInit
  end
  object Timer1: TTimer
    Interval = 40
    OnTimer = Timer1Timer
    Left = 232
    Top = 48
  end
  object MainMenu1: TMainMenu
    Left = 232
    Top = 8
    object OP: TMenuItem
      Caption = 'Opciones'
      object Color: TMenuItem
        AutoCheck = True
        Caption = 'Solid'
        Checked = True
        Default = True
        GroupIndex = 1
        ImageIndex = 0
        RadioItem = True
        OnClick = SinColorClick
      end
      object SinColor: TMenuItem
        Tag = 1
        AutoCheck = True
        Caption = 'Wireframe'
        GroupIndex = 1
        ImageIndex = 1
        RadioItem = True
        OnClick = SinColorClick
      end
    end
    object Circuito1: TMenuItem
      Caption = 'Circuito'
      object Principiante1: TMenuItem
        AutoCheck = True
        Caption = 'Principiante'
        Checked = True
        Default = True
        ImageIndex = 0
        RadioItem = True
        OnClick = Principiante1Click
      end
      object Intermedio1: TMenuItem
        Tag = 2
        Caption = 'Intermedio'
        ImageIndex = 1
        RadioItem = True
        OnClick = Principiante1Click
      end
      object Avanzado1: TMenuItem
        Tag = 1
        Caption = 'Avanzado'
        ImageIndex = 2
        RadioItem = True
        OnClick = Principiante1Click
      end
    end
    object Tiempo1: TMenuItem
      Caption = 'Tiempo'
      object Dia1: TMenuItem
        Caption = 'Dia'
        Checked = True
        Default = True
        GroupIndex = 2
        ImageIndex = 0
        RadioItem = True
        OnClick = Dia1Click
      end
      object Noche1: TMenuItem
        Tag = 1
        Caption = 'Noche'
        GroupIndex = 2
        ImageIndex = 1
        RadioItem = True
        OnClick = Dia1Click
      end
    end
    object Camaras1: TMenuItem
      Caption = 'Luz'
      object ON2: TMenuItem
        Caption = 'ON'
        Checked = True
        Default = True
        GroupIndex = 4
        ImageIndex = 0
        RadioItem = True
        OnClick = ON2Click
      end
      object OFF2: TMenuItem
        Tag = 1
        Caption = 'OFF'
        GroupIndex = 4
        ImageIndex = 1
        RadioItem = True
        OnClick = ON2Click
      end
    end
    object Niebla1: TMenuItem
      Caption = 'Niebla'
      object ON1: TMenuItem
        Caption = 'ON'
        Checked = True
        Default = True
        GroupIndex = 5
        ImageIndex = 0
        RadioItem = True
        OnClick = ON1Click
      end
      object OFF1: TMenuItem
        Tag = 1
        Caption = 'OFF'
        GroupIndex = 5
        ImageIndex = 1
        RadioItem = True
        OnClick = ON1Click
      end
    end
  end
end
