LibraryUsage = {}

function dump(o)
    if type(o) == 'table' then
        local s = '{ '
        for k,v in pairs(o) do
            if type(k) ~= 'number' then k = '"'..k..'"' end
            s = s .. '['..k..'] = ' .. dump(v) .. ','
        end
        return s .. '} '
    else
        return tostring(o)
    end
end
 
function setLibraryUsage(name, inDirs)
    for k,v in pairs(inDirs) do
        inDirs[k] = path.join(_SCRIPT_DIR, inDirs[k]);
    end
    
    LibraryUsage[name] = function()
        includedirs (inDirs)
        links { name }
    end
end

function uselibrary(name)
    if LibraryUsage[name] == nil then
        error ("In " .. _SCRIPT_DIR .. ": uselibrary():: Undefined library name: \"" .. name .. "\"")
    end
    LibraryUsage[name]()
end
