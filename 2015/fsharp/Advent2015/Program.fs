

open System

[<EntryPoint>]
let main argv =
    match argv with
    | [| "all" |] -> Runner.runAll ()
    | [| day |] ->
        match Int32.TryParse(day) with
        | true, num when 1 <= num && num <= 25 -> Runner.runDay num
        | true, _ | false, _ -> printfn "Enter a number (1 to 25) or 'all'."
    | _ ->  printfn "Usage: Advent2015 <day_number> | all"
    0
