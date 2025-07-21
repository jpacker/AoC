my $test = q:to/END/;
    ULL
    RRDDD
    LURDL
    UUUUD
    END

my @posToCode1[3;3] =
[
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
];

my @posToCode2[5;5] = 
[
    [Nil, Nil, 1, Nil, Nil],
    [Nil, 2, 3, 4, Nil],
    [5, 6, 7, 8, 9],
    [Nil, 'A', 'B', 'C', Nil],
    [Nil, Nil, 'D', Nil, Nil] 
];

sub addDelta(List $pos, List $delta, @shapedArray) {
    my @newPos = $pos.Array;
    for ^2 {
        my $new = $pos[$_] + $delta[$_];
        if $new >= 0 && $new < @shapedArray.shape[$_] {
            @newPos[$_] = $new;
        }
    }
    if @shapedArray[@newPos[0]; @newPos[1]].defined {
        return @newPos.List
    }
    else {
        return $pos
    }
}

my $code1 = "";
my $code2 = "";
my $pos1 = (1, 1);
my $pos2 = (2, 0);

#my @input = $test.lines;
my @input = "../inputs/day02.txt".IO.lines;
for @input -> $line {
    for $line.comb -> $c {
        my List $change;
        given $c {
            when 'U' { $change = (-1, 0) }
            when 'D' { $change = (1, 0) }
            when 'L' { $change = (0, -1) }
            when 'R' { $change = (0, 1) }
        }
        $pos1 = addDelta($pos1, $change, @posToCode1);
        $pos2 = addDelta($pos2, $change, @posToCode2);
    }
    $code1 ~= @posToCode1[$pos1[0]; $pos1[1]];
    $code2 ~= @posToCode2[$pos2[0]; $pos2[1]];
}

say $code1;
say $code2;