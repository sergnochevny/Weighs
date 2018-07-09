
Weighsps.dll: dlldata.obj Weighs_p.obj Weighs_i.obj
	link /dll /out:Weighsps.dll /def:Weighsps.def /entry:DllMain dlldata.obj Weighs_p.obj Weighs_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Weighsps.dll
	@del Weighsps.lib
	@del Weighsps.exp
	@del dlldata.obj
	@del Weighs_p.obj
	@del Weighs_i.obj
