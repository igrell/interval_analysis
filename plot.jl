using Plots
rectangle(x0, y0, x1, y1) = Shape(x0 .+ [0,x1,x1,0], y0 .+ [0,0,y1,y1])
rectanglePair = [rectangle,rectangle]
rectangles = [];
open("/home/igor/Documents/Kod/Tutorial/Validated_numerics/interval_analysis/cmake-build-debug/output.txt","r") do file
    for line in eachline(file)
        lineVector = parse.(rectanglePair,line)
        print(lineVector,"\n")
        # append!(rectangles,rectangle())
    end
end
