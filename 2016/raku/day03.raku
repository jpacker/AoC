my $test = q:to/END/;
    541  588  421
    827  272  126
    END

#my $input = $test;
my $input = "../inputs/day03.txt".IO;

sub isValid(@t) {
    return False if @t[0] + @t[1] <= @t[2];
    return False if @t[1] + @t[2] <= @t[0];
    return False if @t[2] + @t[0] <= @t[1];
    return True;
}

my $countValid = 0;
for $input.lines.cache -> $line {
    my $newLine = $line.trim;
    next if !$newLine;
    my @triangle = $newLine.words.map(+*);
    $countValid += 1 if isValid(@triangle);
}

say "Part 1: {$countValid}";

$countValid = 0;

for $input.lines.batch(3) -> @group {
    next if @group.elems != 3;
    my @transposed = [Z] @group.map(*.trim.words.map(+*));
    for @transposed -> @arr {
        $countValid += 1 if isValid(@arr)
    }
}

say "Part 2: {$countValid}";
