# PDDL Parser #

This is meant to be very simple PDDL parser. It should produce a mostly faithful
representation of a planning domain and an optional set of problem instances.

## Supported Fragment of PDDL ##

The parser is meant to deal with a fragment of PDDL2.1. Specifically, it is
supposed to handle the basic STRIPS fragment, augmented with types, numeric
fluents, and negative preconditions. Types are limited to simple inheritance
(i.e., without `either`).

In addition, the parser also allow for a simple form of non-deterministic
effects. The keyword `maybe` can be applied to atomic effects to signify that
the effect may or not be applied.
