( define ( domain trucky )
  ( :requirements :fluents :typing )
  ( :types
    box - locatable
    locatable - object
    location - object
    truck - locatable )
  ( :constants
    depot - location )
  ( :predicates
    ( at ?x - locatable ?l - location )
    ( in ?b - box ?t - truck ) )
  ( :functions
    ( max-weight ?t - truck )
    ( weight ?x - locatable ) )
  ( :action load
    :parameters ( ?t - truck ?b - box ?l - location )
    :precondition ( and ( at ?t ?l ) ( at ?b ?l ) ( <= ( + ( weight ?t ) ( weight ?b ) ) ( max-weight ?t ) ) )
    :effect ( and ( not ( at ?b ?l ) ) ( in ?b ?t ) ( increase ( weight ?t ) ( weight ?b ) ) ) )
  ( :action move
    :parameters ( ?t - truck ?from - location ?to - location )
    :precondition ( and ( at ?t ?from ) )
    :effect ( and ( not ( at ?t ?from ) ) ( at ?t ?to ) ) )
  ( :action unload
    :parameters ( ?t - truck ?b - box ?l - location )
    :precondition ( and ( at ?t ?l ) ( in ?b ?t ) )
    :effect ( and ( not ( in ?b ?t ) ) ( at ?b ?l ) ( decrease ( weight ?t ) ( weight ?b ) ) ) )
 )
