local function readFile(filePath)
    local file = io.open(filePath, "r")
    if not file then
        error("Could not open file " .. filePath)
    end
    local content = file:read("a")
    file:close()
    return content
end

local filePath = "../inputs/day01.txt"
local fileContent = readFile(filePath)
local openCount = select(2, string.gsub(fileContent, "%(", ""))
local closeCount = select(2, string.gsub(fileContent, "%)", ""))
local floor = openCount - closeCount
print("Part 1: " .. floor)

-- local openCount2 = 0
-- local closeCount2 = 0
-- local openBraceCode = utf8.codepoint("(")
-- local closeBraceCode = utf8.codepoint(")")
-- for i, c in utf8.codes(fileContent) do
--     if c==openBraceCode then
--         openCount2 = openCount2 + 1
--     elseif c==closeBraceCode then
--         closeCount2 = closeCount2 + 1
--     end
-- end

-- local floor2 = openCount2 - closeCount2
-- print("Floor2: " .. floor2)