module Days.Day04

// This solution is not very F#-like but I wanted to see
// what it takes in F# to use dotnet constructs to prevent
// unnecessary memory allocations, and how much time it saves.
// The code that prevents memory allocations is above 33% faster
// than the following code which is only slightly faster than
// a python solution.
// let md5 = MD5.Create()
//   let target = String.replicate numZeroes "0"
//   let rec findIndex index =
//       let inputBytes = Encoding.ASCII.GetBytes(input + index.ToString())
//       let hashBytes = md5.ComputeHash(inputBytes)
//       let hashString = Convert.ToHexString(hashBytes)
//       if hashString.StartsWith(target) then
//           index
//       else
//           findIndex (index + 1)
//   findIndex 1

open System
open System.Security.Cryptography
open System.Text

let private solver numZeroes (input: string) =
    let target = String.replicate numZeroes "0"
    let inputBytes = Array.zeroCreate<byte> (input.Length + 32)

    Encoding.ASCII.GetBytes(input, 0, input.Length, inputBytes, 0) |> ignore

    let encodingBytes = Array.zeroCreate<byte> 10
    let hashBytes = Array.zeroCreate<byte> MD5.HashSizeInBytes
    let hexBuffer = Array.zeroCreate<char> (MD5.HashSizeInBytes * 2)
    let intBuffer = Array.zeroCreate<char> 10

    let rec findIndex (index: int32) =
        let intSpan = Span(intBuffer)
        let mutable written = 0
        index.TryFormat(intSpan, &written) |> ignore

        let bytesWritten =
            Encoding.ASCII.GetBytes(intSpan.Slice(0, written), Span(encodingBytes))

        Array.Copy(encodingBytes, 0, inputBytes, input.Length, bytesWritten)

        MD5.HashData(ReadOnlySpan(inputBytes, 0, input.Length + bytesWritten), Span(hashBytes))
        |> ignore

        let hexSpan = Span(hexBuffer)

        let mutable charsWritten = 0

        Convert.TryToHexString(ReadOnlySpan(hashBytes), hexSpan, &charsWritten)
        |> ignore

        if MemoryExtensions.Equals(hexSpan.Slice(0, numZeroes), target, StringComparison.InvariantCulture) then
            index
        else
            findIndex (index + 1)

    findIndex 1

let solve () =
    let input = "ckczppom"
    let part1 = solver 5 input
    let part2 = solver 6 input
    printfn $"Part 1: {part1}"
    printfn $"Part 2: {part2}"
