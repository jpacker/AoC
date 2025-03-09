module Days.Day03

let private move (x, y) =
    function
    | '^' -> (x, y + 1)
    | 'v' -> (x, y - 1)
    | '<' -> (x - 1, y)
    | '>' -> (x + 1, y)
    | _ -> (x, y)

let private initialState = Set.singleton (0, 0), (0, 0)

let private deliverPresents (moves: char seq) =
    let step (visited, pos) c =
        let newPos = move pos c
        Set.add newPos visited, newPos

    Seq.fold step initialState moves |> fst

let private filterEveryNth n offset =
    Seq.indexed >> Seq.filter (fun (i, _) -> (i + offset) % n = 0) >> Seq.map snd

let public solve () : unit =

    let input = System.IO.File.ReadAllText("../../inputs/day03.txt").Trim()

    let part1 = input |> deliverPresents |> Set.count

    let part2 =
        let santaVisited = input |> filterEveryNth 2 0 |> deliverPresents
        let robotVisited = input |> filterEveryNth 2 1 |> deliverPresents

        Set.union santaVisited robotVisited |> Set.count

    printfn $"\tPart 1: {part1}"
    printfn $"\tPart 2: {part2}"
