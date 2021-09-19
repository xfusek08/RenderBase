_libIncludeMap = {}

function exportLibIncludes(libName, libIncludes)
    for k,v in pairs(libIncludes) do
        libIncludes[k] = path.join(_SCRIPT_DIR, libIncludes[k]);
    end
    _libIncludeMap[libName] = libIncludes
end

function importLibIncludes(name)
    if _libIncludeMap[name] == nil then
        error ("In " .. _SCRIPT_DIR .. ": importLibIncludes():: Undefined library name: \"" .. name .. "\"")
    end
    return _libIncludeMap[name]
end
