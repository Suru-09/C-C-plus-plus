# Plagiarism Detection Tool

## How To Use

    
This tool has 2 modes:

        -p from pair_comparison
        -t for tabular
    
1) If we use pair_comparison, we will be able to compare 2 files and see the
            differences between them, like how many words repeat.
   
2) If we use tabular mode we should enter the path for a directory that has multipe
            files in it, after that we call pair_comparison and do that for all the com-
            binations possible in the directory.
    

## Technical

1) We have 2 namespaces: 
   
        - first one is called utility
        - second one is called LCS

    Namespace called utility:
   
        - has 2 functions: tabular and pair_comparison
        They are called depending on the program arguments
        (-t for tabular and -p for pair_comparison)
   
   Namespace called LCS:

        - contains multiple functions:
        algorithm_B and algorithm_C are part of the Hirschberg optimization
        for space
        
        lcs_without_table is a function used only when we have tabular mode,
        because it is faster than my implementation of algorithm_B (probably it
        is related to the vector<vector<int>> situation )

        And then we have 2 more helper functions called selectFromVector, respectively
        init_matrix.

        selectFromVector - is given a range between i and j, and extracts the strings
        from the vector of strings in that range

        init_matrix - initializes the columns of a given matrix, which has the form
        vector<vector<int>>

### NOTE
#### ***Created this algorithm based on the:***

    'A Linear Space Algorithm for Computing Maximal
    Common Subsequences' paper from Princeton University

    link for the paper:
        https://www.ics.uci.edu/~dan/pubs/p341-hirschberg.pdf        