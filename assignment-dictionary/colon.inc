%ifndef last_node
	%define last_node 0
%else
	%error "Single-line macro 'last_node' already exists. The program may not work correctly"    
%endif


%ifnmacro colon 2
    %macro colon 2
    	%ifid %2
    		%2:
    			dq last_node			;next_node address
                %define last_node %2    ;override value of las_node
    			db %1, 0                ;key
    		                            ;The value is defined after the macro
    	%else
    		%error "%2 cannot be a label"
    	%endif    
    %endmacro    
%else
	%error "Macro 'colon 2' already exists. The program may not work correctly"
%endif
