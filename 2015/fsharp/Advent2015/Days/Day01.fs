module Days.Day01

open System.Text

let public solve () : unit =
    let input =
        System.IO.File.ReadAllText("../../inputs/day01.txt", Encoding.UTF8).Trim()

    let nums = [| for c in input -> if c = '(' then 1 else -1 |]
    let part2 =
        nums
        |> Seq.scan (+) 0
        |> Seq.indexed
        |> Seq.find (fun (_, s) -> s = -1)
        |> fst
    printfn $"\tPart 1: {Array.sum nums}"
    printfn $"\tPart 2: {part2}"
