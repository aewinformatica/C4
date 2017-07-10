.const
l2_clog_addunicode	dq	4AAAE0h
l2_clog_add			dq	4aa950h

.code

; implementace metod CLog
?Add@CLog@@QEAAXW4LogType@1@PEBDZZ	proc
		jmp		[l2_clog_add]
?Add@CLog@@QEAAXW4LogType@1@PEBDZZ	endp

?Add@CLog@@QEAAXW4LogType@1@PEB_WZZ	proc
		jmp		[l2_clog_addunicode]
?Add@CLog@@QEAAXW4LogType@1@PEB_WZZ	endp

END
