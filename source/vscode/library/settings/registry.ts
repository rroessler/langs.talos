/// Vendor Modules
import * as vscode from 'vscode';

/// VSC Modules
import { Output } from '@/vscode/output';
import { Product } from '@/vscode/product';

/// Package Modules
import { Schema } from './schema';

/** Schema Registry. */
export namespace Registry {
    //  PROPERTIES  //

    /** The available settings defaults. */
    const m_defaults: Schema = {
        'server.executablePath': '',
        'server.loggingLevel': Output.Level.WARN,
    };

    //  PUBLIC METHODS  //

    /** Gets the settings title to be used. */
    export const section = () => Product.identifier;

    /** Handles showing the underlying settings. */
    export const open = () =>
        vscode.commands.executeCommand<any>(
            'workbench.action.openSettings',
            `@ext:${Product.identifier}.${Product.identifier}-lang`,
        );

    /** Gets the entire configuration. */
    export const all = (): Readonly<Schema> => {
        return Object.keys(m_defaults).reduce(
            (settings, key) => ({ ...settings, [key]: get(key as keyof Schema) }),
            {} as Schema, // prepare the default set of settings to inherit
        );
    };

    /**
     * Handles getting a settings value.
     * @param key               Key of settings.
     * @param fallback          Optional fallback.
     */
    export const get = <K extends keyof Schema>(key: K, fallback = m_defaults[key]) =>
        m_configuration().get<Schema[K]>(key) ?? fallback;

    /**
     * Listens for a configuration change.
     * @param key               Key that changed.
     * @param callback          Event callback.
     */
    export function listen(callback: (settings: Schema) => any): vscode.Disposable;
    export function listen<K extends keyof Schema>(key: K, callback: (value: Schema[K]) => any): vscode.Disposable;
    export function listen(key: string | Function, callback?: Function): vscode.Disposable {
        if (typeof key === 'string') return m_listenKeyChanged(key as keyof Schema, callback as any);
        else return m_listenAllChanged((callback = key) as any); // otherwise default to all handler
    }

    //  PRIVATE METHODS  //

    /** Handles getting the underlying configuration. */
    function m_configuration() {
        return vscode.workspace.getConfiguration(section());
    }

    //  EVENT HANDLERS  //

    /**
     * Handles subscribing to any changes.
     * @param callback              Callback to bind.
     */
    function m_listenAllChanged(callback: (settings: Schema) => any) {
        return vscode.workspace.onDidChangeConfiguration((event) => {
            if (event.affectsConfiguration(section())) callback(all());
        });
    }

    /**
     * Handles subscribing to a key-change.
     * @param key                   Key that changed.
     * @param callback              Callback to bind.
     */
    function m_listenKeyChanged<K extends keyof Schema>(key: K, callback?: (value: Schema[K]) => any) {
        // ignore if the callback is invalid at all
        if (typeof callback === 'undefined') return vscode.Disposable.from();

        // get the original value to be compared against
        let previous = get(key);

        // and subscribe to the incoming configuration changes
        return vscode.workspace.onDidChangeConfiguration((event) => {
            // ignore if the workspace was not affected
            if (!event.affectsConfiguration(section())) return;

            // then we get the incoming value
            const current = get(key);

            // if they are different, then delegate
            if (previous !== current) callback((previous = current));
        });
    }
}
