grammar InstructionGrammar {
    token TOP { <instruction>+ % [',' \s*] }
    token instruction { <turn> <distance> }
    token turn { 'L' | 'R' }
    token distance { \d+ }
}

class Coord {
    has Int $.x;
    has Int $.y;

    method WHICH { ValueObjAt.new("{self.^name}|$.x,$.y") }
}

class InstructionActions {
    has $!x = 0;
    has $!y = 0;
    has $!direction = 'N';
    has SetHash $!visited = <"0,0">.SetHash;
    has $!first_revisit = Nil;
    
    method TOP($/) {
        my $final_dist = $!x.abs + $!y.abs;
        my $revisit_dist = $!first_revisit.defined ?? ($!first_revisit[0].abs + $!first_revisit[1].abs) !! 'None';
        make { final => $final_dist, first_revisit => $revisit_dist };
    }
    
    method instruction($/) {
        self!update_position($<turn>.Str, $<distance>.Int);
    }
    
    method !update_position(Str $turn, Int $distance) {
        my %directions = (
            'N' => { 'L' => 'W', 'R' => 'E' },
            'S' => { 'L' => 'E', 'R' => 'W' },
            'E' => { 'L' => 'N', 'R' => 'S' },
            'W' => { 'L' => 'S', 'R' => 'N' }
        );
        
        $!direction = %directions{$!direction}{$turn};
        
        for 1..$distance {
            given $!direction {
                when 'N' { $!y++ }
                when 'S' { $!y-- }
                when 'E' { $!x++ }
                when 'W' { $!x-- }
            }
            my $loc = Coord.new(:x($!x), :y($!y));
            if !$!first_revisit.defined && $loc ∈ $!visited {
                $!first_revisit = [$!x, $!y];
            }
            $!visited.set($loc);
        }
    }
}

my $input = '../inputs/day01.txt'.IO.slurp.chomp;
my $parsed = InstructionGrammar.parse($input, :actions(InstructionActions.new));
say $parsed.made;