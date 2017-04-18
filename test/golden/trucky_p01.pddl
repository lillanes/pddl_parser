( define ( problem trucky-p01 )
  ( :domain trucky )
  ( :objects
    b01 - box
    b02 - box
    b03 - box
    l01 - location
    l02 - location
    t01 - truck
    t02 - truck )
  ( :init
    ( at t01 depot )
    ( at t02 depot )
    ( at b01 l01 )
    ( at b02 l01 )
    ( at b03 l02 )
    ( = ( weight t01 ) 0 )
    ( = ( weight t02 ) 0 )
    ( = ( weight b01 ) 10 )
    ( = ( weight b02 ) 20 )
    ( = ( weight b03 ) 30 )
    ( = ( max-weight t01 ) 30 )
    ( = ( max-weight t02 ) 20 ) )
  ( :goal ( and ( at b01 depot ) ( at b02 depot ) ( at b03 depot ) ) )
 )
