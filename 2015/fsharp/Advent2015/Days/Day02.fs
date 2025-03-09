module Days.Day02

open System

let public solve () : unit =
    let input = IO.File.ReadLines("../../inputs/day02.txt")

    let measurements =
        [| for line in input -> line.Split("x") |> Array.map Int32.Parse |> Array.sort |]

    let part1 =
        measurements
        |> Array.sumBy (fun sides ->
            2 * (sides[0] * sides[1] + sides[1] * sides[2] + sides[2] * sides[0])
            + sides[0] * sides[1])

    let part2 =
        measurements
        |> Array.sumBy (fun sides -> sides[0] * 2 + sides[1] * 2 + (Array.reduce (*) sides))

    printfn $"\tPart 1: {part1}"
    printfn $"\tPart 2: {part2}"
