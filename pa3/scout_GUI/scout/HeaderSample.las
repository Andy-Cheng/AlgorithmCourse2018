color lightgray 100 100 100       // set lightgray as RGB=100,100,100
color blue 0 0 33                 // overwrite default color blue as RGB=0,0,33
property pt delay double 50       // attach property "delay" to type pt, and the default value is 50
property pt loading double 21.5   // attach property "loading" to type pt, and the default value is 21.5
property pt name string unknown   // attach property "name" to type pt, and the default value is unknown
endheader
pt 100 50 green 0  delay 70 loading 10.5 name sink_01    !!pt: delay>=50                        // green point(square) at (100, 50), has delay=70, loading=10.5, name=sink_01 #>related search # pt: delay>=50
pt 50 50 green 0  loading 5.7 name sink_02               !!pt: delay>=40 #pt: loading>=20       // green point(square) at (50, 50), has delay=50(default), loading=5.7, name=sink_02 #>related search # pt: delay>=40 # pt: loading>=20
pt 100 100 teal 1  name sink_03 loading 19 delay 55      !!pt: loading<=20 && delay>50          // teal point(triangle) at (100, 100), has delay=55, loading=19, name=sink_03 #>related search # pt: loading<=20 && delay>50
pt 50 100 blue 1  name sink_04                                                                  // blue(the overwritten color) point(triangle) at (50, 100), has delay=50(default), loading=21.5(default), name=sink_04
