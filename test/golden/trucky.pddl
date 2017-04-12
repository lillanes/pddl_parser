( define ( domain trucky )
  ( :requirements :typing :fluents )
  ( :types
    box - locatable
    truck - locatable
    location - object
    locatable - object )
  ( :constants
    depot - location )
  ( :predicates
    ( at ?x - locatable ?l - location )
    ( in ?b - box ?t - truck ) )
  ( :functions
    ( max-weight ?t - truck )
    ( weight ?x - locatable ) )
  ( :action move
    :parameters ( ?t - truck ?from - location ?to - location )
    :precondition ( at ?t ?from )
    :effect ( and ( not ( at ?t ?from ) ) ( at ?t ?to ) ) )
  ( :action load
    :parameters ( ?t - truck ?b - box ?l - location )
    :precondition ( and ( at ?t ?l ) ( at ?b ?l ) ( <= ( + ( weight ?t ) ( weight ?b ) ) ( max-weight ?t ) ) )
    :effect ( and ( not ( at ?b ?l ) ) ( in ?b ?t ) ( increase ( weight ?t ) ( weight ?b ) ) ) )
  ( :action unload
    :parameters ( ?t - truck ?b - box ?l - location )
    :precondition ( and ( at ?t ?l ) ( in ?b ?t ) )
    :effect ( and ( not ( in ?b ?t ) ) ( at ?b ?l ) ( decrease ( weight ?t ) ( weight ?b ) ) ) )
 )
