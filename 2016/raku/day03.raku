my $test = q:to/END/;
    541  588  421
    827  272  126
    END

#my $input = $test;
my $input = "../inputs/day03.txt".IO;

sub isValid(@triangle) {
    my $valid = True;
    for 0..2 {
            my ($a, $b, $c) = @triangle.rotate($_);
            if $a + $b <= $c {
                $valid = False;
                last;
            }
    }
    $valid;
}

my $countValid = 0;
for $input.lines.cache -> $line {
    my $newLine = $line.trim;
    next if !$newLine;
    my @triangle = $newLine.split(/ \s+ /).map(+*);
    $countValid += 1 if isValid(@triangle);
}

say "Part 1: {$countValid}";

$countValid = 0;

for $input.lines.batch(3) -> @group {
    next if @group.elems != 3;
    my @transposed = [Z] @group.map(*.trim.split(/ \s+ /).map(+*));
    for @transposed -> @arr {
        $countValid += 1 if isValid(@arr)
    }
}

say "Part 2: {$countValid}";
