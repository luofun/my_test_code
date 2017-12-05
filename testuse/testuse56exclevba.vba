Public NNN As Integer


Private Declare PtrSafe Function GetPrivateProfileString Lib "kernel32" _
    Alias "GetPrivateProfileStringA" _
    (ByVal lpApplicationName As String, _
    ByVal lpKeyName As Any, _
    ByVal lpDefault As String, _
    ByVal lpReturnedString As String, _
    ByVal nSize As Long, _
    ByVal lpFileName As String) As Long
Private Declare PtrSafe Function WritePrivateProfileString Lib "kernel32" _
    Alias "WritePrivateProfileStringA" _
    (ByVal lpApplicationName As String, _
    ByVal lpKeyName As Any, _
    ByVal lpString As Any, _
    ByVal lpFileName As String) As Long

Public Function ReadFromIni(ByVal IniFile As String, ByVal Section As String, ByVal Key As String, ByVal DefaultValue As String) As String
    Dim strRtn As String
    strRtn = Space(1024)
    Dim lngRtn As Long
    lngRtn = GetPrivateProfileString(Section, Key, DefaultValue, strRtn, 255, IniFile)
    If lngRtn > 0 Then
        strRtn = Trim(strRtn)
        ReadFromIni = Mid(strRtn, 1, Len(strRtn) - 1)
    Else
        ReadFromIni = DefaultValue
    End If
End Function


Private Sub test()
    Dim strIniFile As String
    strIniFile = ActiveWorkbook.Path & "\newform.ini"
    
    strValue = ReadFromIni(strIniFile, "begin", "gpionum", "null")
    Cells(1, 1) = "GPIOnums"
    Cells(1, 2) = strValue
    Dim gpionum As Integer
    gpionum = CInt(Val(strValue))
    
    strValue = ReadFromIni(strIniFile, "begin", "typenum", "null")
    Cells(1, 4) = "typenum"
    Cells(1, 5) = strValue
    Dim typenum As Integer
    typenum = CInt(Val(strValue))
    
    NNN = typenum
    
    Dim defaultgpioname As String
    defaultgpioname = ReadFromIni(strIniFile, "begin", "gpiodefaultname", "unknown")
    Cells(1, 7) = "GPIOdefaultname"
    Cells(1, 8) = defaultgpioname
    
    For i = 0 To gpionum - 1
        Dim name As String
        name = ReadFromIni(strIniFile, "spname", CStr(i), defaultgpioname)
        
        If (name = defaultgpioname) Then
            name = name + Chr(65 + i / 24) + CStr(i Mod 24)
        End If
        
        Cells(i + 3, 1) = name
    Next i
    
    For i = 1 To typenum
        Dim typename As String
        typename = ReadFromIni(strIniFile, "type", CStr(i), "unknown")
        Cells(2, 2 + i) = typename
        
        Dim rangebegin As String
        rangebegin = Chr(65 + i + 1) + "3"
        
        Dim rangeend As String
        rangeend = Chr(65 + i + 1) + CStr(gpionum + 2)
        
        Dim info As String
        info = ReadFromIni(strIniFile, "info", typename, "unknown")
        
        'Cells(5 + gpionum, i) = typename
        
        Dim substr As String
        Dim subnum As Integer
        
        substr = ReadFromIni(strIniFile, typename, "num", "unknown")
        subnum = CInt(Val(substr))
        
        Dim selectstr As String
        selectstr = ""
        For j = 1 To subnum
            Dim subsubstr As String
            subsubstr = ReadFromIni(strIniFile, typename, CStr(j), "unknown")
            'Cells(5 + gpionum + j, i) = subsubstr
            
            selectstr = selectstr + subsubstr
            If (j <> subnum) Then
                selectstr = selectstr + ","
            End If
            
        Next j
        
        Range(rangebegin + ":" + rangeend).Select
            With Selection.Validation
                .Delete
            '.Add Type:=xlValidateInputOnly, AlertStyle:=xlValidAlertStop, Operator _
            ':=xlBetween
            .Add Type:=xlValidateList, AlertStyle:=xlValidAlertStop, Operator:= _
            xlBetween, Formula1:=selectstr
            .IgnoreBlank = True
            .InCellDropdown = True
            .InputTitle = typename
            .ErrorTitle = ""
            .InputMessage = info
            .ErrorMessage = ""
            .IMEMode = xlIMEModeNoControl
            .ShowInput = True
            .ShowError = True
        End With
    Next i
        

End Sub

Private Sub Worksheet_Change(ByVal Target As Range)

    Dim rngDV As Range
    Dim oldVal As String
    Dim newVal As String
    If Target.Count > 1 Then GoTo exitHandler
    
    On Error Resume Next
    Set rngDV = Cells.SpecialCells(xlCellTypeAllValidation)
    On Error GoTo exitHandler
    
    If rngDV Is Nothing Then GoTo exitHandler
    
    If Intersect(Target, rngDV) Is Nothing Then
       
    Else
      Application.EnableEvents = False
      newVal = Target.Value
      Application.Undo
      oldVal = Target.Value
      Target.Value = newVal
      If Target.Column >= 3 And Target.Column <= 3 + NNN Then
        If oldVal = "" Then
          
          Else
          If newVal = "" Then
          
          Else
          Target.Value = oldVal _
            & "|" & newVal
            
          End If
        End If
      End If
    End If
    
exitHandler:
      Application.EnableEvents = True
End Sub