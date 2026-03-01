/// Node Modules
import * as fs from 'node:fs';
import * as path from 'node:path';

/// Vendor Modules
import * as vscode from 'vscode';

/// JSON Modules
import _ from '~/package.json';

/** Product Constants. */
export namespace Product {
    //  PROPERTIES  //

    /** Handles parsing the underlying package. */
    const m_package = JSON.parse(fs.readFileSync(path.resolve(__dirname, _), 'utf-8'));

    /** Underlying product identifier. */
    export const identifier = m_package.publisher;

    /** Underlying crate file-name. */
    export const crateFile = '_crate.jsonc';

    /** Short descriptor name. */
    export const shortName = identifier[0].toUpperCase() + identifier.slice(1);

    /** Long descriptor name. */
    export const longName = m_package.displayName;

    /** The version of the extension. */
    export const version = m_package.version;

    /** Executable name expected. */
    export const executable = `${identifier}${process.platform === 'win32' ? '.exe' : ''}`;

    /** Document Filter Selector. */
    export const selector = { scheme: 'file', language: identifier } satisfies vscode.DocumentSelector;
}
