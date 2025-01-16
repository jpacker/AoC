
{-# LANGUAGE OverloadedStrings #-}

import qualified Data.ByteString.Lazy.Char8 as B

parensChoice :: Char -> Int
parensChoice '(' = 1
parensChoice ')' = -1

part1 :: B.ByteString -> Int
part1 = B.foldl' (\acc c -> acc + parensChoice c) 0

-- add one when ( and subtract one when ) but break when the count is < 0
-- report the position when the count is < 0
part2 :: B.ByteString -> Int
part2 = loop 0 0
    where
        loop pos acc bs
            | acc < 0 = pos
            | otherwise = case B.uncons bs of
                Nothing -> -1
                Just (c, bs') -> loop (pos + 1) (acc + parensChoice c) bs'

main :: IO ()
main = do
    parens <- head . B.lines <$> B.readFile "../inputs/day01.txt"
    print $ part1 parens
    print $ part2 parens
