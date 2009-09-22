arithmeticsProcessData <- function(d) {
    d <- processData(d, paste(d$benchmark.arch, d$datatype, d$benchmark.name),
        pchkey = "benchmark.name", colorkey = "datatype")
    d$key <- pasteNN(d$datatype, d$benchmark.arch)
    d
}

for(data in list(rbind(sse, simple, lrb))) {
    data <- arithmeticsProcessData(data)

    mychart4(data, data$benchmark.name, orderfun = function(d) order(d$Op_per_cycle.median),
        column = "Op_per_cycle", xlab = "Compares per Cycle", main = "Arithmetics")
}

sse    <- arithmeticsProcessData(sse)
lrb    <- arithmeticsProcessData(lrb)
simple <- arithmeticsProcessData(simple)

plotSpeedup(sse, simple, lrb, main = "Arithmetics",
    speedupColumn = "Op_per_cycle",
    datafun = function(d, ref) list(key = d$datatype)
    )

# vim: sw=4 et filetype=r sts=4 ai
