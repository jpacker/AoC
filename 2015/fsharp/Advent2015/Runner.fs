module Runner

open System.Reflection

let public getImplementedDays () : System.Type array =
    Assembly.GetExecutingAssembly().GetTypes()
    |> Array.filter (fun t -> t.FullName.StartsWith("Days.Day") && t.IsClass && t.DeclaringType = null)
    |> Array.sortBy _.FullName

let private callSolve (t: System.Type) : unit =
    match t.GetMethod("solve") with
    | null -> printfn $"No solve method for {t.FullName}"
    | methodInfo -> methodInfo.Invoke(null, [||]) |> ignore

let public runAll () : unit =
    getImplementedDays ()
    |> Array.iter (fun t ->
        printfn $"Running {t.Name}"
        callSolve t)

let public runDay (day: int) : unit =
    let moduleName = $"Days.Day{day:D2}"

    match Assembly.GetExecutingAssembly().GetType(moduleName) with
    | null -> printfn $"Day {day} not found."
    | t ->
        printfn $"Running {t.Name}"
        callSolve t
