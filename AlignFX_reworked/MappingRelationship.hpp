#include<iostream>

enum class MappingRelationship {
    EQUIVALENCE = '=',
    SUPERCLASS = '&gt;',
    SUBCLASS = '&lt;',
    OVERLAP = '^',
    UNKNOWN = '?',
    INCLUSION = '⊆'
};

