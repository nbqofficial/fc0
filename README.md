# fc0
#### Chess engine compatible with UCI (universal chess interface) protocol. Currently rated around 2100 on lichess.org

## Board representation
- mailbox board representation (120 square vector)
- pieces are represented with numerical values (ex. white queen = 9)
- boards can be parsed from FEN

## Move generation
- moves are generated with a classical approach
- custom move structure (score, from, to, promote, castling, en-pas)
- moves are sorted by score (to prioritize moves for alpha-beta search)
- able to generate quiet and capture moves separately (useful in quiescence)

## Evaluation
- basic material evaluation
- piece-square tables (optimal square for each piece type)
- piece mobility
- support for basic neural network evaluation

## Search
- multiple search algorithm implementations
- basic negamax
- probabilistic negamax
- monte-carlo tree search
- enhanced with alpha-beta and null-move pruning
- quiescence search to reduce horizon effect
