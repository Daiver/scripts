import Data.List

minFromSeq seq n = take n $ sort seq
maxFromSeq n = reverse . (take n) . reverse . sort

main = do
    print $  maxFromSeq 5 [2, 200, 123, 3, 4, 5, 10000] --minFromSeq [2, 342, 56456, 7565, -90, 11, 34, -8] 5
