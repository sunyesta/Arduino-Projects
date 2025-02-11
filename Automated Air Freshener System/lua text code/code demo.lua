local 


local Window = {}


function setup()
	local lcd = Lcd.new(pins)
	local nextItemBtn = Button.new(PIN_NXT_ITEM_BTN)
	local selectItemBtn = Button.new(PIN_SEL_ITEM_BTN)
	table.insert(lcd.Windows, "menu")
	table.insert(lcd.Windows, "shots_and_temp")
	table.insert(lcd.Windows, "set spray delay") --refreshed every 2 seconds

	lcd.Windows.Menu = Window.new()
    lcd.Windows.Menu.Selections = {"Shots and temp","Set spray delay", "testing mode"}
    lcd.Windows.Menu:SetText()
	function lcd.Windows.Menu:SelectItem()
        
    end
	lcd.Windows.ShotsAndTemp = Window.new()
	lcd.Windows.SetSprayDelay = Window.new()

	lcd.ActiveWindow = lcd.Windows.ShotsAndTemp

	nextItemBtn.Pressed:Connect(function()
		lcd.ActiveWindow:NextItem()
	end)

	selectItemBtn.Pressed:Connect(function()
		lcd.ActiveWindow:SelectItem()
	end)
end
