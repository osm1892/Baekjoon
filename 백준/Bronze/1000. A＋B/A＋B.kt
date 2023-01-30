fun main(args: Array<String>) {
    println(readLine()?.split(' ')?.sumOf { x: String -> x.toInt() })
}