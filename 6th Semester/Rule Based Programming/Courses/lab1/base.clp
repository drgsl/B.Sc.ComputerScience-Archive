; (assert (passionGames))
; (assert (passionUnity))

; (clear)
; (reset)


(printout t "do u like games?" crlf)

(defrule read_PassionGames
(passionGames)
=> 
(assert (passionGames(read)))
)

(printout t "do u like unity?" crlf)
(defrule read_PassionUnity
(passionUnity)
=> 
(assert (passionUnity(read)))
)


(defrule gameDesign
(passionGames1)
(passionUnity1)
=>
(assert (gameDesign))
)

