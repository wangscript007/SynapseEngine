Strict

Graphics 800,600


Local fs:TStream = WriteFile("font.pf")

For Local i:Int = 0 Until 255

	Local c:String = "0"
	
	c[0] = i
	

	Print "T:"+c
	Cls
	DrawText(c,0,0)
	 
	
	Local pix:TPixmap= GrabPixmap(0,0,TextWidth(c),TextHeight(c))
	WriteInt(fs,TextWidth(c))
	WriteInt(fs,TextHeight(c))
	
	Print "CW:"+TextWidth(c)
	Print "CH:"+TextHeight(C);
	
	For Local y:Int =0  Until TextHeight(C)
	For Local x:Int = 0 Until TextWidth(C)
	
		Local byt:Byte Ptr = pix.pixelptr(x,y)
	
		WriteByte(fs,byt[0])
		WriteByte(Fs,byt[1])
		WriteByte(fs,Byt[2])
		If((byt[0]+byt[1]+byt[2])>64)
			WriteByte(fs,255)
		Else
			WriteByte(Fs,0)		
		End If
	
	Next
	Next
		

Next

fs.flush()

CloseFile(fs)
