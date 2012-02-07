DELETE FROM `command` WHERE `name` IN('vip token','vip token add');
INSERT INTO `command` (`name`,`security`,`help`) VALUES
('vip token', 0, 'Syntaxe: .vip token\n\nExibe quantos VIP Tokens voce tem.'),
('vip token add', 4, 'Syntaxe: .vip token add #conta #tokens\n\nAdiciona ou remove tokens de uma conta.');
